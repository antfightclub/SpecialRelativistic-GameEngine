#include "relativity_app.hpp"

// Application
#include "mve_camera.hpp"
#include "systems/lattice_wireframe_system.hpp"
#include "mve_buffer.hpp"
#include "lattice.hpp"
#include "player.hpp"

// Math namespace
#include "relativity/math/Matrix44.hpp"
#include "relativity/math/Vector3.hpp"
#include "relativity/math/WorldLine.hpp"

// GLM 
#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm.hpp>
#include <gtc/constants.hpp>
#include <gtx/quaternion.hpp>



//std libs
#include <cassert>
#include <chrono>
#include <stdexcept>
#include <array>
#include <iostream>

namespace mve {

	RelativityApp::RelativityApp() {
		globalPool = MveDescriptorPool::Builder(mveDevice)
			.setMaxSets(MveSwapChain::MAX_FRAMES_IN_FLIGHT * 2)
			.addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, MveSwapChain::MAX_FRAMES_IN_FLIGHT * 2) // times 2 due to usage of Global Ubo + Lattice Ubo 
			.addPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, MveSwapChain::MAX_FRAMES_IN_FLIGHT)
			.build();
		//UIPool = MveDescriptorPool::Builder(mveDevice)
		//	.setMaxSets(MveSwapChain::MAX_FRAMES_IN_FLIGHT)
		//	.addPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, MveSwapChain::MAX_FRAMES_IN_FLIGHT)
		//	.buildUIPool();

		loadGameObjects();

		setupDearImgui();
	}

	RelativityApp::~RelativityApp() {}
	
	void RelativityApp::run() {
		
		//// Create an image sampler buffer for Dear ImGui rendering
		//std::vector<std::unique_ptr<MveBuffer>> dearImGuiBuffers(MveSwapChain::MAX_FRAMES_IN_FLIGHT);
		//for (int i = 0; i < dearImGuiBuffers.size(); i++) {
		//	dearImGuiBuffers[i] = std::make_unique<MveBuffer>(
		//		mveDevice,
		//		sizeOf()
		//	);
		//}


		// Create Uniform Buffer Object for lattice rendering
		std::vector<std::unique_ptr<MveBuffer>> latticeUboBuffers(MveSwapChain::MAX_FRAMES_IN_FLIGHT);
		for (int i = 0; i < latticeUboBuffers.size(); i++) {
			latticeUboBuffers[i] = std::make_unique<MveBuffer>(
				mveDevice,
				sizeof(LatticeUbo),
				1,
				VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
			);
			latticeUboBuffers[i]->map();
		}

		MveBuffer latticeUboBuffer{
			mveDevice,
			sizeof(LatticeUbo),
			MveSwapChain::MAX_FRAMES_IN_FLIGHT,
			VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
			mveDevice.properties.limits.minUniformBufferOffsetAlignment,
		};
		latticeUboBuffer.map();
		

		// Create Uniform Buffer Object for Global UBO buffers (projection, view, inverse view matrices and ambient light color)
		std::vector<std::unique_ptr<MveBuffer>> globalUboBuffers(MveSwapChain::MAX_FRAMES_IN_FLIGHT);
		for (int i = 0; i < globalUboBuffers.size(); i++) {
			globalUboBuffers[i] = std::make_unique<MveBuffer>(
				mveDevice,
				sizeof(GlobalUbo),
				1,
				VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
			);
			globalUboBuffers[i]->map();
		}

		MveBuffer globalUboBuffer{
			mveDevice,
			sizeof(GlobalUbo),
			MveSwapChain::MAX_FRAMES_IN_FLIGHT,
			VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
			mveDevice.properties.limits.minUniformBufferOffsetAlignment,
		};
		globalUboBuffer.map();
		
		


		auto globalSetLayout = MveDescriptorSetLayout::Builder(mveDevice)
			.addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 1U) // Global Ubo 
			.addBinding(1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 1U)
			.build();
		
		std::vector<VkDescriptorSet> descriptorSets(MveSwapChain::MAX_FRAMES_IN_FLIGHT);
		for (int i = 0; i < descriptorSets.size(); i++) {	
			auto globalBufferInfo = globalUboBuffers[i]->descriptorInfo();
			auto latticeBufferInfo = latticeUboBuffers[i]->descriptorInfo();
			MveDescriptorWriter(*globalSetLayout, *globalPool)
				.writeBuffer(0, &globalBufferInfo)
				.writeBuffer(1, &latticeBufferInfo)
				.build(descriptorSets[i]);
		}

		LatticeWireframeSystem latticeRenderSystem{ mveDevice, mveRenderer.getSwapChainRenderPass(), globalSetLayout->getDescriptorSetLayout()};
		MveCamera camera{};
		//camera.setViewDirection(glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 1.f));
		//camera.setViewTarget(glm::vec3(4.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f));
		
		glm::mat4 cameraView{ 1.0 };
		

		auto viewerObject = MveGameObject::createGameObject();
		//viewerObject.transform.translation.z = 4.f;

		

		Player player{ mveWindow , viewerObject, Math::Vector4D{}, Math::EntityState{} };

		//void (*updateKeypressFcnPointer) (int, int) { nullptr };
		//void (*fcnPtr) (int, int) {	}
		//mveWindow.setPlayerPointer();

		//glfwSetWindowUserPointer(mveWindow.getGLFWwindow(), &player);
		//KeyboardInputController cameraController{};
		

		auto currentTime = std::chrono::high_resolution_clock::now();
		float timeSince = 0.f; // used to count time between frames!

		while (!mveWindow.shouldClose()) {
			glfwPollEvents();

			auto newTime = std::chrono::high_resolution_clock::now();
			float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
			float dt = frameTime - timeSince;
						
	
			float aspect = mveRenderer.getAspectRatio();

			camera.setPerspectiveProjection(glm::radians(100.f), aspect, 0.01f, 1000.0f);

			if (auto commandBuffer = mveRenderer.beginFrame()) {
				int frameIndex = mveRenderer.getFrameIndex();
				FrameInfo frameInfo{
					frameIndex,
					frameTime,
					commandBuffer,
					camera,
					descriptorSets[frameIndex],
					gameObjects
				};
							

				// ********** Update **********

				player.Action(mveWindow.getGLFWwindow(), dt);

				// Should get a GLM rotation matrix directly, but haven't gotten around to firmly establishing coordinate conventions yet
				Math::Quaternion playerOrientation = player.quaternion;
				
				// Establish camera view matrix
				glm::vec3 playerPos = glm::vec3{ (float)player.P.X.getX(), (float)player.P.X.getY(), (float)player.P.X.getZ() };
				glm::quat orientation = glm::quat{ (float)playerOrientation.t, (float)playerOrientation.x, (float)playerOrientation.y, (float)playerOrientation.z };				
				glm::mat4 rotate = glm::toMat4(orientation); 
				glm::mat4 translate = glm::mat4(1.0f);
				translate = glm::translate(translate, playerPos);
				cameraView = glm::inverse(translate*rotate);
				viewerObject.transform.translation = playerPos;
				
				camera.setView(cameraView);

				// update global ubo buffer
				GlobalUbo globalUbo{};
				globalUbo.projection = camera.getProjection();
				globalUbo.view = camera.getView();
				globalUbo.inverseView = glm::mat4{ 1.0 };
				globalUbo.ambientLightColor = { 1.f, 1.f, 1.f, .02f };
				globalUboBuffers[frameIndex]->writeToBuffer(&globalUbo);
				globalUboBuffers[frameIndex]->flush();

				// This is supposed to center the lattice wireframe grid on the player, but is unused currently.
				// TODO: Establish coordinate system conventions.
				glm::vec3 Xp = glm::vec3{ player.P.X.getX(), player.P.X.getY(), player.P.X.getZ() };
				int xo = int(int(Xp.x / (N / L)) * (N / L));
				int yo = int(int(Xp.y / (N / L)) * (N / L));
				int zo = int(int(Xp.z / (N / L)) * (N / L));
				Math::Matrix44 U{};
				
				// I think Lorentz might need some sign flips... 
				// TODO: Work on establishing coordinate system conventions and make sure to change Math namespace accordingly
				U = Math::Matrix44::Lorentz(player.P.U); // Does not work if you normalize U LOL
				glm::mat4 lorentz = U.toGLM();

		/*		if (movedir.length() > 0.0) {
					U = Math::Matrix44::Lorentz(Math::Vector4D{ 1.0, movedir.x, movedir.y , movedir.z });
				}
				else {
					U = Math::Matrix44::Lorentz(Math::Vector4D{ 1.0, 0.0, 0.0, 0.0 });
				}*/
				
				//Math::Vector4D u = Math::Vector4D{};

				//U = Math::Matrix44::Lorentz(u);
				/*std::cout << "********** START OF PRINTING MATRICES **********" << std::endl;

				std::cout << "** View Matrix:" << std::endl;
				printGLMMat4(camera.getView());
				std::cout << "** Inverse View Matrix:" << std::endl;
				printGLMMat4(camera.getInverseView());
				std::cout << "** Projection Matrix:" << std::endl;
				printGLMMat4(camera.getProjection());

				glm::mat4 temp = U.toGLM();
				std::cout << "** Lorentz matrix U \n" << U << std::endl;
				std::cout << "** Lorentz to GLM" << std::endl;
				printGLMMat4(temp);

				std::cout << "Xo.x = " << xo << ", Xo.y = " << yo << ", Xo.z = " << zo << std::endl;
				std::cout << "Xp.x = " << Xp.x << ", Xp.y = " << Xp.y << ", Xp.z = " << Xp.z << '\n' << std::endl;
*/


				// ********** Dear ImGui **********

				ImGui_ImplVulkan_NewFrame();
				ImGui_ImplGlfw_NewFrame();
				ImGui::NewFrame();

				static float f = 0.05;
				static int counter = 0;

				ImGui::Begin("Haiii babe :3c");
				

				float framerate = ImGui::GetIO().Framerate;

				ImGui::Text("Total frame time = %.4f [s]", frameTime);
				ImGui::Text("deltaTime = %.3f [ms]", dt*1000);
				ImGui::Text("FPS = %.0f", framerate);

				ImGui::NewLine();

				std::array<float, 4> playerPosFloat = { (float)player.P.X.getT(), (float)player.P.X.getX(), (float)player.P.X.getY(), (float)player.P.X.getZ() };
				std::array<float, 4> playerVelFloat = { (float)player.P.U.getT(), (float)player.P.U.getX(), (float)player.P.U.getY(), (float)player.P.U.getZ() };
				std::array<float, 4> Xp_float = { 0.f, (float)Xp.x, (float)Xp.y, (float)Xp.z };
				std::array<float, 4> Xo_float = { 0.f, (float)xo, (float)yo, (float)zo };

				enum ContentsType { CT_Text, CT_FillButton };
				static ImGuiTableFlags flags = ImGuiTableFlags_Borders;
				static bool display_headers = true;
				static int contents_type = CT_Text;
				// Player table
				ImGui::BeginTable("Player", 4, flags);
				ImGui::TableSetupColumn("Pos");
				ImGui::TableSetupColumn("Vel");
				ImGui::TableSetupColumn("Xp");
				ImGui::TableSetupColumn("Xo");
				ImGui::TableHeadersRow();

				for (int row = 0; row < 4; row++) {
					ImGui::TableNextRow();
					for (int column = 0; column < 4; column++)
					{
						ImGui::TableSetColumnIndex(column);
						if (column == 0) {
							ImGui::Text("%.3f", playerPosFloat[row]);
						}
						else if (column == 1) {
							ImGui::Text("%.3f", playerVelFloat[row]);
						}
						else if (column == 2) {
							ImGui::Text("%.3f", Xp_float[row]);
						}
						else if (column == 3) {
							ImGui::Text("%.3f", Xo_float[row]);
						}
					}
				}
				ImGui::EndTable();

				// Lorentz
				double g = player.P.U.getGamma(); // Lorentz Factor
				double u = std::sqrt(1.0 - (1.0 /(g*g))); // Fraction of c
				double v = Math::c * u;
				

				ImGui::NewLine();
				ImGui::Text("speed: %f [m/s]", v);
				ImGui::Text("c = %f", u);
				ImGui::Text("Lorentz factor: %.3f", g);
				

				ImGui::NewLine();
				// View matrix 
				ImGui::Text("View matrix");
				ImGui::BeginTable("View Matrix", 4, flags);
				ImGui::TableSetupColumn("col0");
				ImGui::TableSetupColumn("col1");
				ImGui::TableSetupColumn("col2");
				ImGui::TableSetupColumn("col3");
				ImGui::TableHeadersRow();

				for (int row = 0; row < 4; row++) {
					ImGui::TableNextRow();
					for (int column = 0; column < 4; column++)
					{
						ImGui::TableSetColumnIndex(column);
						ImGui::Text("%+.3f", (float)cameraView[column][row]);
					}
				}
				ImGui::EndTable();

				ImGui::NewLine();
				// Lorentz matrix 
				ImGui::Text("Lorentz matrix");
				ImGui::BeginTable("Lorentz matrix", 4, flags);
				ImGui::TableSetupColumn("col0");
				ImGui::TableSetupColumn("col1");
				ImGui::TableSetupColumn("col2");
				ImGui::TableSetupColumn("col3");
				ImGui::TableHeadersRow();

				for (int row = 0; row < 4; row++) {
					ImGui::TableNextRow();
					for (int column = 0; column < 4; column++)
					{
						ImGui::TableSetColumnIndex(column);
						ImGui::Text("%+.3f", (float)lorentz[column][row]);
					}
				
				}
				ImGui::EndTable();

				//ImGui::NewLine();



		/*		if (ImGui::Button("Buttone"))
					counter++;
				ImGui::SameLine();
				ImGui::Text("counter = %f", counter);*/

				ImGui::End();

				// ********** Dear ImGui **********

				
				

				// TODO: update lattice ubo buffer with a lorentz matrix calculated in accordance with special relativity
				LatticeUbo latticeUbo{};
				latticeUbo.Xp = glm::vec3{ Xp.x, Xp.y, Xp.z};
				latticeUbo.Xo = glm::vec3{ xo,   yo,   zo };
				latticeUbo.Lorentz = lorentz;
				latticeUboBuffers[frameIndex]->writeToBuffer(&latticeUbo);
				latticeUboBuffers[frameIndex]->flush();
				latticeUboBuffer.flushIndex(frameIndex);

				std::cout << " *********** Render begin\n";

				// Render
				mveRenderer.beginSwapChainRenderPass(commandBuffer);
				
				//VkCommandBuffer command_buffer = mveRenderer.;

				// order matters (if semitransparency is involved)
				latticeRenderSystem.renderWireframe(frameInfo);

				//mveRenderer.endSwapChainRenderPass(commandBuffer);
				
				//mveRenderer.beginSwapChainRenderPass(commandBuffer, uiRenderPass);
				ImGui::Render();
				ImDrawData* draw_data = ImGui::GetDrawData();
				const bool is_minimized = (draw_data->DisplaySize.x <= 0.0f || draw_data->DisplaySize.y <= 0.0f);
				if (!is_minimized) {
					ImGui_ImplVulkan_RenderDrawData(draw_data, commandBuffer); // this is probably a big no-no
				}
				mveRenderer.endSwapChainRenderPass(commandBuffer);
				

				mveRenderer.endFrame();		
				std::cout << " *********** Render ended \n";
			}

			timeSince = frameTime;
		}

		vkDeviceWaitIdle(mveDevice.device());

		// Dear ImGui cleanup here should definitely be done somewhere else
		ImGui_ImplVulkan_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void RelativityApp::loadGameObjects() {
		// generate lattice
		// Lattice needs to be .... better...
		Lattice lattice{N, L, 20, 1, 1.0};
		
		//lattice.writeVerticesToFile();
		//lattice.writeIndicesToFile();
		
		//std::cout << "Writing vertices to file...\n";
		auto vertices = lattice.getVertices();
		//std::cout << "Writing indices to file...\n";
		auto indices = lattice.getIndices();
		//std::cout << "finished writing vertices in Vertices.txt and indices in Indices.txt\nvk

		//std::cout << "printing out ALL lattice vertices!" << std::endl;
		//
		//// This takes a long time!
		//for (auto& vert : vertices) {
		//	std::cout << "{ " << vert.x << ", " << vert.y << ", " << vert.z << " }\n";
		//}
		//std::cout << "printing out ALL lattice indices!" << '\n';
		//for (auto& indc : indices) {
		//	std::cout << "index = " << indc << "\n";
		//}


		std::shared_ptr<MveModel> mveModel = MveModel::createModelFromStdVector(mveDevice, vertices, indices);

		auto latticeGameObject = MveGameObject::createGameObject();

		latticeGameObject.model = mveModel;
		latticeGameObject.transform.translation = { 0.f, 0.f, 0.f };
		latticeGameObject.transform.scale = glm::vec3{ 1.f, 1.f, 1.f };
		gameObjects.emplace(latticeGameObject.getId(), std::move(latticeGameObject));
	}

	
	//	I think I would do a looooooot better if I followed Sascha Willem's example
	//	https://github.com/SaschaWillems/Vulkan/blob/master/examples/imgui/main.cpp
	//	And make a separate class for ImGui perhaps!!
	void RelativityApp::setupDearImgui() {
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		
		// Setup Dear ImGui style
		ImGui::StyleColorsDark();

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForVulkan(mveWindow.getGLFWwindow(), true);
		ImGui_ImplVulkan_InitInfo init_info = {};
		init_info.Instance = mveDevice.getInstance();
		init_info.PhysicalDevice = mveDevice.getPhysicalDevice();
		init_info.Device = mveDevice.device();

		QueueFamilyIndices q = mveDevice.findPhysicalQueueFamilies();
		if (!q.graphicsFamilyHasValue) {
			throw std::runtime_error("setupDearImgui(): Device has no graphics queue!");
		}
		init_info.QueueFamily = q.graphicsFamily;
		init_info.Queue = mveDevice.graphicsQueue();
		init_info.PipelineCache = VK_NULL_HANDLE;
		//init_info.DescriptorPool = VK_NULL_HANDLE;
		init_info.DescriptorPoolSize = 1; //= globalPool.get();
		init_info.Allocator = nullptr;
		init_info.MinImageCount = MveSwapChain::MAX_FRAMES_IN_FLIGHT;
		init_info.ImageCount = MveSwapChain::MAX_FRAMES_IN_FLIGHT;
		createImguiRenderPass(uiRenderPass);
		init_info.RenderPass = uiRenderPass;
		init_info.Subpass = 0;
		init_info.CheckVkResultFn;
		ImGui_ImplVulkan_Init(&init_info);

		//ImGui::ImGui_ImplVulkan_Data* bd = ImGui_ImplVulkan_GetBackendData();

	//	io.BackendRendererUserData->vulkan

		ImGui_ImplVulkan_CreateFontsTexture();
	}


	void RelativityApp::createImguiRenderPass(VkRenderPass& uiRenderPass) {
		VkAttachmentDescription attachment = {};
		attachment.format = VK_FORMAT_B8G8R8A8_SRGB;
		attachment.samples = VK_SAMPLE_COUNT_1_BIT;
		attachment.loadOp =/* wd->ClearEnable ? VK_ATTACHMENT_LOAD_OP_CLEAR :*/ VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
		VkAttachmentReference color_attachment = {};
		color_attachment.attachment = 0;
		color_attachment.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		// NOTE!: I added depth attachment even thought it is not needed by ImGui
		// This is to enforce renderpass / pipeline compatibility...
		// Later on when I eventually rewrite this entire engine, I should
		// Definitely make sure I can use vulkan dynamic rendering to avoid
		// this requirement and setting shit myself
		// Could also just, ya know, make sure I implement a backend for ImGui myself
		/*
		VkAttachmentDescription depthAttachment{};
		depthAttachment.format = mveRenderer.getSwapChainDepthFormat();
		depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
		depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
		VkAttachmentReference depth_attachment = {};
		depth_attachment.attachment = 1;
		depth_attachment.layout = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL;
		*/


		VkSubpassDescription subpass = {};
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &color_attachment;
		//subpass.pDepthStencilAttachment = &depth_attachment;
		
		
		VkSubpassDependency dependency = {};
		dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
		dependency.dstSubpass = 0;
		dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.srcAccessMask = 0;
		dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

		std::array<VkAttachmentDescription, /*2*/1> attachments = { attachment /*, depthAttachment*/};

		VkRenderPassCreateInfo info = {};
		info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		info.attachmentCount = static_cast<uint32_t>(attachments.size());
		info.pAttachments = attachments.data();
		info.subpassCount = 1;
		info.pSubpasses = &subpass;
		info.dependencyCount = 1;
		info.pDependencies = &dependency;
		if (vkCreateRenderPass(mveDevice.device(), &info, nullptr, &uiRenderPass) != VK_SUCCESS) {
			throw std::runtime_error("Failed to create Dear ImGui render pass!");
		}
		//err = vkCreateRenderPass(device, &info, allocator, &wd->RenderPass);
		//check_vk_result(err);
	}	
}