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
		UIDescriptorPool = MveDescriptorPool::Builder(mveDevice)
			.setPoolFlags(VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT)
			.setMaxSets(MveSwapChain::MAX_FRAMES_IN_FLIGHT)
			.addPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, MveSwapChain::MAX_FRAMES_IN_FLIGHT)
			.build();

		loadGameObjects();

		setupDearImgui();
	}

	RelativityApp::~RelativityApp() {}
	
	void RelativityApp::run() {
		// Create Uniform Buffer Object for LatticeUbo, which contains relativity stuff for the wireframe lattice
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
		
		// Descriptor set layout for GlobalUbo and LatticeUbo
		auto globalSetLayout = MveDescriptorSetLayout::Builder(mveDevice)
			.addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 1U) // GlobalUbo 
			.addBinding(1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 1U) // LatticeUBo
			.build();
		
		// Write the descriptor sets to buffers
		std::vector<VkDescriptorSet> descriptorSets(MveSwapChain::MAX_FRAMES_IN_FLIGHT);
		for (int i = 0; i < descriptorSets.size(); i++) {	
			auto globalBufferInfo = globalUboBuffers[i]->descriptorInfo();
			auto latticeBufferInfo = latticeUboBuffers[i]->descriptorInfo();
			MveDescriptorWriter(*globalSetLayout, *globalPool)
				.writeBuffer(0, &globalBufferInfo)
				.writeBuffer(1, &latticeBufferInfo)
				.build(descriptorSets[i]);
		}

		// Wireframe Lattice around player
		LatticeWireframeSystem latticeRenderSystem{ mveDevice, mveRenderer.getSwapChainRenderPass(), globalSetLayout->getDescriptorSetLayout()};
		MveCamera camera{};		
		glm::mat4 cameraView{ 1.0 }; // This will be updated later in the update loop
		
		auto viewerObject = MveGameObject::createGameObject(); // Game object to hold camera position
		
		Player player{ mveWindow , viewerObject, Math::Vector4D{}, Math::EntityState{} }; // Game player

		// Used to have the keyboard input controller defined here
		// But the functionality has since been moved to MveWindow
		// In favor of using it to update a keymap
		// Keymap is then read from by Player.action() inside update loop.
		
		// Set up time related variables
		auto currentTime = std::chrono::high_resolution_clock::now();
		float timeSince = 0.f; // used to count time between frames!

		// Main application update loop
		while (!mveWindow.shouldClose()) { 
			glfwPollEvents(); // poll GLFW library for user input

			// Calculate frame times 
			// This is a very naive implementation! As it stands this is the only mechanism for time-steps
			// which means that movement is framerate-dependent instead of having a fixed-time step for physics etc.
			auto newTime = std::chrono::high_resolution_clock::now();
			float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count(); // seconds since first frame
			float dt = frameTime - timeSince;																			 // delta time in seconds
				
			float aspect = mveRenderer.getAspectRatio();

			camera.setPerspectiveProjection(glm::radians(100.f), aspect, 0.01f, 1000.0f);

			// poll this every update loop, but only actaully begin new frame if one is ready from the swap chain. 
			// MveRenderer (and by extension MveSwapChain) is responsible for acquiring next image for rendering
			if (auto result = mveRenderer.beginFrame()) {
				int frameIndex = mveRenderer.getFrameIndex(); 
				
				// ********** Acquire command buffers and set up FrameInfo **********
				
				// We have a command buffer for the main application rendering (world, game) and a separate one for the UI.
				std::array<VkCommandBuffer, 2> cmdBuffers = mveRenderer.getCurrentFrameCommandBuffers();
				FrameCommandBuffers frameCommandBuffers{
					cmdBuffers[0],		// Main command buffers (world, game)
					cmdBuffers[1]		// UI command buffers
				};

				// Struct used to help render systems
				FrameInfo frameInfo{
					frameIndex,
					frameTime,
					frameCommandBuffers,
					camera,
					descriptorSets[frameIndex],
					gameObjects
				};
				
				// ********** Update game **********

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
				
				camera.setView(cameraView); // Sets the camera view matrix

				// Update buffer holding GlobalUbo
				GlobalUbo globalUbo{};
				globalUbo.projection = camera.getProjection();
				globalUbo.view = camera.getView();
				globalUbo.inverseView = glm::mat4{ 1.0 };
				globalUbo.ambientLightColor = { 1.f, 1.f, 1.f, .02f };
				globalUboBuffers[frameIndex]->writeToBuffer(&globalUbo);
				globalUboBuffers[frameIndex]->flush();

				// This is supposed to center the lattice wireframe grid on the player, but is unused currently since I have been struggling without established coord conventions
				// TODO: Establish coordinate system conventions.
				glm::vec3 Xp = glm::vec3{ player.P.X.getX(), player.P.X.getY(), player.P.X.getZ() };
				int xo = int(int(Xp.x / (N / L)) * (N / L));
				int yo = int(int(Xp.y / (N / L)) * (N / L));
				int zo = int(int(Xp.z / (N / L)) * (N / L));
				Math::Matrix44 U{};
				
				// I think Lorentz might need some sign flips... 
				// TODO: Work on establishing coordinate system conventions and make sure to change Math namespace accordingly
				// Actually: Make sure to flip the axes here so they correspond to the shader convention, or have a way to convert between MveModel conventions and shader conventions!
				U = Math::Matrix44::Lorentz(player.P.U); // Does not work if you normalize U LOL
				glm::mat4 lorentz = U.toGLM();

				// TODO: update lattice ubo buffer with a lorentz matrix calculated in accordance with special relativity
				// Update buffer holding LatticeUbo
				LatticeUbo latticeUbo{};
				latticeUbo.Xp = glm::vec3{ Xp.x, Xp.y, Xp.z };
				latticeUbo.Xo = glm::vec3{ xo,   yo,   zo };
				latticeUbo.Lorentz = lorentz;
				latticeUboBuffers[frameIndex]->writeToBuffer(&latticeUbo);
				latticeUboBuffers[frameIndex]->flush();
				latticeUboBuffer.flushIndex(frameIndex);


				// ********** Update Dear ImGui state **********
				// This could perhaps be separated into its own function, or perhaps be implemented in a render system.
				// As it stands it is pretty messy code. But if it is its own class I will have to implement some way
				// For it to get all the states I want. Could be done with a struct later on.

				ImGui_ImplVulkan_NewFrame();
				ImGui_ImplGlfw_NewFrame();
				ImGui::NewFrame();

				ImGui::Begin("Debug UI");
				
				float framerate = ImGui::GetIO().Framerate; // Rolling average of last 60 frames

				ImGui::Text("Total frame time = %.3f [s]", frameTime);
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
				// Player info table
				ImGui::BeginTable("Player", 4, flags);
				ImGui::TableSetupColumn("Pos"); // Position
				ImGui::TableSetupColumn("Vel"); // Velocity
				ImGui::TableSetupColumn("Xp");	// Currently the player position
				ImGui::TableSetupColumn("Xo");  // Currently corresponds to a lattice index, sorta
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
				ImGui::End();

				// ********** End Dear ImGui **********

							
				// ********** Rendering **********

				// Ordinary render systems go here!
				mveRenderer.beginSwapChainRenderPass(frameCommandBuffers.mainCommandBuffer);
				// order matters (if semitransparency is involved)
				latticeRenderSystem.renderWireframe(frameInfo);
				mveRenderer.endSwapChainRenderPass(frameCommandBuffers.mainCommandBuffer);
				
				// UI rendering
				mveRenderer.beginUIRenderPass(frameCommandBuffers.UICommandBuffer);
				ImGui::Render();
				ImDrawData* draw_data = ImGui::GetDrawData();
				const bool is_minimized = (draw_data->DisplaySize.x <= 0.0f || draw_data->DisplaySize.y <= 0.0f);
				if (!is_minimized) {
					ImGui_ImplVulkan_RenderDrawData(draw_data, frameCommandBuffers.UICommandBuffer);
				}
				mveRenderer.endUIRenderPass(frameCommandBuffers.UICommandBuffer); // Ends renderpass
				
				// Ends command buffers.
				mveRenderer.endFrame();	
			}

			timeSince = frameTime; // assign timeSince to frameTime at beginning of the loop, such that next loop it can be subtracted from frameTime to calculate deltaTime
		}

		vkDeviceWaitIdle(mveDevice.device()); // Wait for device to become idle before main.cpp destroys RelativityApp (do not destroy application while e.g. rendering is happening)

		// Dear ImGui cleanup here could be somewhere else, but I'm entirely unsure...
		ImGui_ImplVulkan_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void RelativityApp::loadGameObjects() {
		// generate lattice

		/*
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
		*/


		std::shared_ptr<MveModel> debugModel = MveModel::createDebuggingModel(mveDevice);
		auto dbgGameObject = MveGameObject::createGameObject();

		dbgGameObject.model = debugModel;
		dbgGameObject.transform.translation = { 0.f, 0.f, 0.f };
		dbgGameObject.transform.scale = glm::vec3{ 1.f,1.f,1.f };
		gameObjects.emplace(dbgGameObject.getId(), std::move(dbgGameObject));
	}

	
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
		//createImguiRenderPass(uiRenderPass);
		
		init_info.RenderPass = mveRenderer.getUIRenderPass();
		init_info.Subpass = 0;
		init_info.CheckVkResultFn;
		ImGui_ImplVulkan_Init(&init_info);
		
		ImGui_ImplVulkan_CreateFontsTexture();
	}
}