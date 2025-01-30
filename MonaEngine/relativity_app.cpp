#include "relativity_app.hpp"

// Application
#include "mve_camera.hpp"
#include "systems/lattice_wireframe_system.hpp"
#include "systems/sr_render_system.hpp"
#include "mve_buffer.hpp"
#include "player.hpp"
#include "enemy.hpp"

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

using namespace m4sta;

namespace mve {

	RelativityApp::RelativityApp() {
		// Initialization: Allocate a descriptor pool for the main rendering system and one for DearImGui.
		globalPool = MveDescriptorPool::Builder(mveDevice)
			.setMaxSets(MveSwapChain::MAX_FRAMES_IN_FLIGHT * 2)
			.addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, MveSwapChain::MAX_FRAMES_IN_FLIGHT * 3) // times 3 due to usage of Global Ubo + Lattice Ubo + specialrelativityUBO
			.build();
		UIDescriptorPool = MveDescriptorPool::Builder(mveDevice)
			.setPoolFlags(VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT)
			.setMaxSets(MveSwapChain::MAX_FRAMES_IN_FLIGHT)
			.addPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, MveSwapChain::MAX_FRAMES_IN_FLIGHT)
			.build();

		// Load game objects into the world
		loadGameObjects();

		// Set up the state for Dear ImGui
		setupDearImgui();
	}

	RelativityApp::~RelativityApp() {} // MveWindow, MveDevice, and MveRenderer, as well as MveGameObject map and MveDescriptorPool have their own mechanisms for cleanup
	
	void RelativityApp::run() {

		// Create Uniform Buffer Object for SpecialRelativityUbo, contains relativity stuff between other entities and player
		std::vector<std::unique_ptr<MveBuffer>> specialRelativityUboBuffers(MveSwapChain::MAX_FRAMES_IN_FLIGHT);
		for (int i = 0; i < specialRelativityUboBuffers.size(); i++) {
			specialRelativityUboBuffers[i] = std::make_unique<MveBuffer>(
				mveDevice,
				sizeof(SpecialRelativityUbo),
				1,
				VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
			);
			specialRelativityUboBuffers[i]->map();
		}

		MveBuffer specialRelativityUboBuffer{
			mveDevice,
			sizeof(SpecialRelativityUbo),
			MveSwapChain::MAX_FRAMES_IN_FLIGHT,
			VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
			mveDevice.properties.limits.minUniformBufferOffsetAlignment,
		};
		specialRelativityUboBuffer.map();


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
			.addBinding(2, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 1U) // SpecialRelativityUbo
			.build();
		
		// Write the descriptor sets to buffers
		std::vector<VkDescriptorSet> descriptorSets(MveSwapChain::MAX_FRAMES_IN_FLIGHT);
		for (int i = 0; i < descriptorSets.size(); i++) {	
			auto globalBufferInfo = globalUboBuffers[i]->descriptorInfo();
			auto latticeBufferInfo = latticeUboBuffers[i]->descriptorInfo();
			auto srBufferInfo = specialRelativityUboBuffers[i]->descriptorInfo();
			MveDescriptorWriter(*globalSetLayout, *globalPool)
				.writeBuffer(0, &globalBufferInfo)
				.writeBuffer(1, &latticeBufferInfo)
				.writeBuffer(2, &srBufferInfo)
				.build(descriptorSets[i]);
		}

		// Set up render systems
		LatticeWireframeSystem latticeRenderSystem{ mveDevice, mveRenderer.getSwapChainRenderPass(), globalSetLayout->getDescriptorSetLayout()};
		SRRenderSystem srRenderSystem{ mveDevice, mveRenderer.getSwapChainRenderPass(), globalSetLayout->getDescriptorSetLayout() };


		MveCamera camera{};		
		glm::mat4 cameraView{ 1.0 }; // This will be updated later in the update loop
		
		auto viewerObject = MveGameObject::createGameObject(); // Game object to hold camera position
		Player player{ mveWindow , viewerObject, Math::Vector4D{}, Math::EntityState{} }; // Game player


		std::shared_ptr<MveModel> cubeModel = MveModel::createModelFromFile(mveDevice, "./models/gay_cube.obj");

		auto enemyObject = MveGameObject::createGameObject(); // The enemy's game object
		enemyObject.model = cubeModel;
		Enemy enemy{ mveWindow, enemyObject, Math::Vector4D{0.0, 3.0, 0.0, 4.0}, Math::EntityState{} };
		enemyObject.transform.translation = { 3.0f, 0.0f, 4.0f };
		gameObjects.emplace(enemyObject.getId(), std::move(enemyObject));

		// Used to have the keyboard input controller defined here
		// But the functionality has since been moved to MveWindow
		// In favor of using it to update a keymap
		// Keymap is then read from by Player.action() inside update loop.
		
		// Set up time related variables
		auto currentTime = std::chrono::high_resolution_clock::now();
		float timeSince = 0.f; // used to count time between frames!
		bool renderLattice = true; // whether to render lattice - set in imgui ui

		//float sta_vel[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

		

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

			camera.setPerspectiveProjection(glm::radians(70.0f), aspect, 0.01f, 1000.0f);

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
				enemy.Action(mveWindow.getGLFWwindow(), dt);

				// Should get a GLM rotation matrix directly instead of this, but will require a rewrite of Math:: namespace
				Math::Quaternion playerOrientation = player.quaternion;
				
				// Establish camera view matrix
				glm::vec3 playerPos = glm::vec3{ (float)player.P.X.getX(), (float)player.P.X.getY(), (float)player.P.X.getZ() };
				glm::quat orientation = glm::quat{ (float)playerOrientation.t, (float)playerOrientation.x, (float)playerOrientation.y, (float)playerOrientation.z };				
				glm::mat4 rotate = glm::toMat4(orientation); 
				glm::mat4 translate = glm::mat4(1.0f);
				//translate = glm::translate(translate, playerPos);
				
				// NOTE: Currently, we do *not* translate the camera view matrix.
				// If we did, we would inadvertedly make sure the Lorentz trans-
				// formation is centered in the origin of the grid.

				cameraView = glm::inverse(translate * rotate);
				viewerObject.transform.translation = playerPos;
				
				camera.setView(cameraView); // Sets the camera view matrix

				glm::mat4 invView = glm::inverse(cameraView); // Inverse camera view matrix

				// Update buffer holding GlobalUbo
				GlobalUbo globalUbo{};
				globalUbo.projection = camera.getProjection();
				globalUbo.view = camera.getView();
				globalUbo.inverseView = invView;
				globalUbo.ambientLightColor = { 1.f, 1.f, 1.f, .02f };
				globalUboBuffers[frameIndex]->writeToBuffer(&globalUbo);
				globalUboBuffers[frameIndex]->flush();

				
				// Xp = player's position in the background frame
				glm::vec3 Xp = glm::vec3{ player.P.X.getX(), player.P.X.getY(), player.P.X.getZ() };

				// Xo = displacement of lattice by Lattice Unit N/L to keep it centered on the player in the vertex shader
				int xo = int(int(Xp.x / (lattice.latticeUnit)) * (lattice.latticeUnit));
				int yo = int(int(Xp.y / (lattice.latticeUnit)) * (lattice.latticeUnit));
				int zo = int(int(Xp.z / (lattice.latticeUnit)) * (lattice.latticeUnit));
				

				double PlayerU[4] = { player.P.U.getT(), player.P.U.getX(), player.P.U.getY(), player.P.U.getZ() };
				
				//m4sta_testing_stuffs(player.P.X, playerLastPosition, dt);

				Math::Matrix44 L{};	
				L = Math::Matrix44::Lorentz(player.P.U); // Lorentz boost matrix : Bg frame -> Player frame
				glm::mat4 lorentz = L.toGLM();			 // .toGLM() transposes the matrix to conform to GLSL conventions
				
				Math::Matrix44 LL{};
				LL = Math::Matrix44::Lorentz(-player.P.U);	// Not sure how to use yet; but it transforms from the player's frame of reference to the background frame of reference.
				glm::mat4 invLorenz = LL.toGLM();
				
				// Update buffer holding LatticeUbo
				LatticeUbo latticeUbo{};
				latticeUbo.Xp = glm::vec3{ Xp.x, Xp.y, Xp.z};
				latticeUbo.Xo = glm::vec3{ xo,   yo,   zo };
				latticeUbo.Lorentz = lorentz;
				latticeUboBuffers[frameIndex]->writeToBuffer(&latticeUbo);
				latticeUboBuffers[frameIndex]->flush();
				latticeUboBuffer.flushIndex(frameIndex);



				EnemyDrawData eDrawData = enemy.getDrawData(player.P.X, L, LL);

				Math::Vector4D dX = eDrawData.X - player.P.X;
				dX.setT(-dX.length()); // spacetime interval
				Math::Vector4D negdX = -dX;
				Math::Vector4D x_p = Math::Matrix44::Lorentz(eDrawData.U).getTransform(negdX);
				
				glm::vec4 xp = glm::vec4{ (float)x_p.getX(), (float)x_p.getY(), (float)x_p.getZ(), (float)x_p.getT() };

				Math::Vector4D dee_X = L.getTransform(dX);
				glm::vec4 dX_playerframe = glm::vec4{ (float)dee_X.getX(), (float)dee_X.getY(), (float)dee_X.getZ(), 0.f };

				// LL   -    player frame to background frame, then background frame to enemy frame
				glm::mat4 L_p2b_b2e = (Math::Matrix44::Lorentz(eDrawData.U) * LL).toGLM();

				// L    -    enemy to player frame
				glm::mat4 L_e2p = (L * Math::Matrix44::Lorentz(-eDrawData.U)).toGLM();

				glm::quat enemyOrientation = glm::quat{ (float)eDrawData.quaternion.t, (float)eDrawData.quaternion.x, (float)eDrawData.quaternion.y, (float)eDrawData.quaternion.z };

				SpecialRelativityUbo srUbo{};
				srUbo.Lorentz = L_e2p;
				srUbo.Lorentz_p2e = L_p2b_b2e;
				srUbo.Rotate = glm::toMat4(enemyOrientation);
				srUbo.dX = dX_playerframe;
				srUbo.xp = xp;
				specialRelativityUboBuffers[frameIndex]->writeToBuffer(&srUbo);
				specialRelativityUboBuffers[frameIndex]->flush();
				specialRelativityUboBuffer.flushIndex(frameIndex);





				// ********** Update Dear ImGui state **********
				// This could perhaps be separated into its own function, or perhaps be implemented in a render system.
				// As it stands it is pretty messy code. But if it is its own class I will have to implement some way
				// For it to get all the states I want. Could be done with a struct later on.
				
				bool debug_open = true;
				bool sta_open = true;

				ImGui_ImplVulkan_NewFrame();
				ImGui_ImplGlfw_NewFrame();
				ImGui::NewFrame();

				if (ImGui::Begin("Debug UI", &debug_open)) {

					float framerate = ImGui::GetIO().Framerate; // Rolling average of last 60 frames

					ImGui::Text("Total frame time = %.3f [s]", frameTime);
					ImGui::Text("deltaTime = %.3f [ms]", dt * 1000);
					ImGui::Text("FPS = %.0f", framerate);

					ImGui::NewLine();

					// Casting the desired values into a convenient format (as well as double->float)
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
								ImGui::Text("%+.3f", playerPosFloat[row]);
							}
							else if (column == 1) {
								ImGui::Text("%+.3f", playerVelFloat[row]);
							}
							else if (column == 2) {
								ImGui::Text("%+.3f", Xp_float[row]);
							}
							else if (column == 3) {
								ImGui::Text("%+.3f", Xo_float[row]);
							}
						}
					}
					ImGui::EndTable();

					// Lorentz 
					double g = player.P.U.getGamma(); // Lorentz Factor
					double u = std::sqrt(1.0 - (1.0 / (g * g))); // Fraction of c
					double v = Math::c * u;

					ImGui::NewLine();
					ImGui::Text("speed: %f [m/s]", v);
					ImGui::Text("c = %f", u);
					ImGui::Text("Lorentz factor: %.3f", g);
					ImGui::NewLine();
					ImGui::Text("Proper Time: %.3f [s]", frameTime);
					ImGui::Text("World  Time: %.3f [s]", player.P.X.getT());

					ImGui::NewLine();
					ImGui::Checkbox("show/hide lattice", &renderLattice);


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
					
				}
				ImGui::End();
				if (ImGui::Begin("Spacetime Algebra", &sta_open)) {
					
					/*
					ImGui::Text("For v1 and v2 make sure they are *timelike* only.");
					ImGui::Text("Just make sure the absolute value of the sum of  ");
					ImGui::Text("the spatial components don't exceed the absolute ");
					ImGui::Text("value of the time component. Note that v1 and v2 ");
					ImGui::Text("DO NOT get normalized.");

					static float v1coord[4] = { 1.f, 0.f, 0.f, 0.f };
					ImGui::SliderFloat4("float4 v1", v1coord, 0.f, 10.f);
					//ImGui::DragFloat4("input float4 v1", v1coord);
					mv v1 =
						(double)v1coord[0] * g0 +
						(double)v1coord[1] * g1 +
						(double)v1coord[2] * g2 +
						(double)v1coord[3] * g3;

					static float v2coord[4] = { 1.f, 0.f, 0.f, 0.f };
					ImGui::SliderFloat4("float4 v2", v2coord, 0.f, 10.f);
					mv v2 =
						(double)v2coord[0] * g0 +
						(double)v2coord[1] * g1 +
						(double)v2coord[2] * g2 +
						(double)v2coord[3] * g3;

					//v1 = unit(v1);
					//v2 = unit(v2);
					mv V = v2 * v1;

					ImGui::Text(v1.c_str());

					if (norm2(v1).get_scalar() >= 0.001f) {
						ImGui::SameLine();
						ImGui::Text(" timelike");
					}
					else if (norm2(v1).get_scalar() <= 0.001f) {
						ImGui::SameLine();
						ImGui::Text(" spacelike");
					}
					else {
						ImGui::SameLine();
						ImGui::Text(" lightlike");
					}

					ImGui::Text(v2.c_str());

					if (norm2(v2).get_scalar() >= 0.001f) {
						ImGui::SameLine();
						ImGui::Text(" timelike");
					}
					else if (norm2(v2).get_scalar() <= 0.001f) {
						ImGui::SameLine();
						ImGui::Text(" spacelike");
					}
					else {
						ImGui::SameLine();
						ImGui::Text(" lightlike");
					}

					ImGui::Text("V = "); 
					ImGui::SameLine();
					ImGui::Text(V.c_str());


					ImGui::NewLine();
					ImGui::Text("For n1 and n2 make sure they are *spacelike* only.");
					ImGui::Text("Just make sure the absolute value of the sum of   ");
					ImGui::Text("the spatial components don't less than the absolute");
					ImGui::Text("value of the time component. Note that n1 and n2  ");
					ImGui::Text("get normalized.");

					static float n1coord[4] = { 0.f, 5.f, 5.f, 5.f };
					ImGui::SliderFloat4("float4 n1", n1coord, 0.f, 10.f);
					//ImGui::DragFloat4("input float4 v1", v1coord);
					mv n1 =
						(double)n1coord[0] * g0 +
						(double)n1coord[1] * g1 +
						(double)n1coord[2] * g2 +
						(double)n1coord[3] * g3;

					static float n2coord[4] = { 0.f, 5.f, 5.f, 5.f };
					ImGui::SliderFloat4("float4 n2", n2coord, 0.f, 10.f);
					mv n2 =
						(double)n2coord[0] * g0 +
						(double)n2coord[1] * g1 +
						(double)n2coord[2] * g2 +
						(double)n2coord[3] * g3;

					n1 = unit(n1);
					n2 = unit(n2);
					mv Q = n2 * n1;

					ImGui::Text(n1.c_str());

					if (norm2(n1).get_scalar() >= 0.001f) {
						ImGui::SameLine();
						ImGui::Text(" timelike");
					}
					else if (norm2(n1).get_scalar() <= 0.001f) {
						ImGui::SameLine();
						ImGui::Text(" spacelike");
					}
					else {
						ImGui::SameLine();
						ImGui::Text(" lightlike");
					}

					ImGui::Text(n2.c_str());

					if (norm2(n2).get_scalar() >= 0.001f) {
						ImGui::SameLine();
						ImGui::Text(" timelike");
					}
					else if (norm2(n2).get_scalar() <= 0.001f) {
						ImGui::SameLine();
						ImGui::Text(" spacelike");
					}
					else {
						ImGui::SameLine();
						ImGui::Text(" lightlike");
					}

					ImGui::Text("Q = ");
					ImGui::SameLine();
					ImGui::Text(Q.c_str());
					*/

					static float vcoord[4] = { 0.f, 0.f, 0.f, 0.f };
					ImGui::SliderFloat4("float4 v (vel)", vcoord, 0.f, 10.f);
					//ImGui::DragFloat4("input float4 v1", v1coord);
					mv v =
						(double)vcoord[0] * g0 +
						(double)vcoord[1] * g1 +
						(double)vcoord[2] * g2 +
						(double)vcoord[3] * g3;
					static float gammaprime0 = 1.0f;
					ImGui::SliderFloat("gammaprime0", &gammaprime0, 1.f, 10.f);
					mv L = v * (gammaprime0 * g0) * (g0);
					
					ImGui::Text("v       = ");
					ImGui::SameLine(); ImGui::Text(v.c_str());
					ImGui::Text("L       = ");
					ImGui::SameLine(); ImGui::Text(L.c_str());
					mv split = L * g0;
					ImGui::Text("L split = "); 
					ImGui::SameLine(); ImGui::Text(split.c_str());
				
				}
				ImGui::End();
				

				// ********** End Dear ImGui **********

							
				// ********** Rendering **********

				//std::cout << "******* RENDER *******" << "\n";

				// Ordinary render systems go here!
				mveRenderer.beginSwapChainRenderPass(frameCommandBuffers.mainCommandBuffer);
				// order matters (if semitransparency is involved)

				if (renderLattice) {
					latticeRenderSystem.renderWireframe(frameInfo, latticeGameObjectID);
				}
				srRenderSystem.render(frameInfo, latticeGameObjectID);
				mveRenderer.endSwapChainRenderPass(frameCommandBuffers.mainCommandBuffer);
				
				// UI rendering happens *after* the ordinary render systems, and uses a separate command buffer
				// Important that it is after, since the ui renderpass transitions the framebuffer for presentation
				mveRenderer.beginUIRenderPass(frameCommandBuffers.UICommandBuffer);
				ImGui::Render();
				ImDrawData* draw_data = ImGui::GetDrawData();
				const bool is_minimized = (draw_data->DisplaySize.x <= 0.0f || draw_data->DisplaySize.y <= 0.0f);
				if (!is_minimized) {
					ImGui_ImplVulkan_RenderDrawData(draw_data, frameCommandBuffers.UICommandBuffer);
				}
				mveRenderer.endUIRenderPass(frameCommandBuffers.UICommandBuffer); // Ends renderpass
				
				// Ends both command buffers and submits framebuffer to presentation queue
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

		auto vertices = lattice.getVertices();
		auto indices = lattice.getIndices();

		std::shared_ptr<MveModel> mveModel = MveModel::createModelFromStdVector(mveDevice, vertices, indices);
		auto latticeGameObject = MveGameObject::createGameObject();

		latticeGameObject.model = mveModel;
		latticeGameObject.transform.translation = { 0.f, 0.f, 0.f };
		latticeGameObject.transform.scale = glm::vec3{ 1.f, 1.f, 1.f };
		
		latticeGameObjectID = latticeGameObject.getId();
		gameObjects.emplace(latticeGameObject.getId(), std::move(latticeGameObject)); // latticeGameObject no longer owned by that handle

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



	void RelativityApp::m4sta_testing_stuffs(Math::Vector4D X, Math::Vector4D lastX, double dt) {
		

		// 4-vector / pseudoscalar
		m4sta::mv I = m4sta::I;

		// 1-vector / spacetime vector 
		m4sta::mv g0 = m4sta::g0;
		m4sta::mv g1 = m4sta::g1;
		m4sta::mv g2 = m4sta::g2;
		m4sta::mv g3 = m4sta::g3;
		
		// 2-vector (on the diagonal)
		m4sta::mv g00 = g0 * g0;
		m4sta::mv g11 = g1 * g1;
		m4sta::mv g22 = g2 * g2;
		m4sta::mv g33 = g3 * g3;

		// 2-vector / bivector 
		m4sta::mv g01 = g0 * g1;	m4sta::mv g10 = g1 * g0;
		m4sta::mv g02 = g0 * g2;	m4sta::mv g20 = g2 * g0;
		m4sta::mv g03 = g0 * g3;	m4sta::mv g30 = g3 * g0;
		m4sta::mv g12 = g1 * g2;	m4sta::mv g21 = g2 * g1;
		m4sta::mv g13 = g1 * g3;	m4sta::mv g31 = g3 * g1;
		m4sta::mv g23 = g2 * g3;	m4sta::mv g32 = g3 * g2;

		// 3-vector / trivector
		m4sta::mv g012 = g0 * I;
		m4sta::mv g013 = g1 * I;
		m4sta::mv g023 = g2 * I;
		m4sta::mv g123 = g3 * I;
		
	    // Pauli basis, sigma_k with k in {1,2,3}
		m4sta::mv sigma1 = g1 ^ g0;
		m4sta::mv sigma2 = g2 ^ g0;
		m4sta::mv sigma3 = g3 ^ g0;

		
		/*
		m4sta::mv lastProperPos = m4sta::g0 * lastX.getT() + m4sta::g1 * lastX.getX() + m4sta::g2 * lastX.getY() + m4sta::g3 * lastX.getZ();
		std::cout << "last   proper position   = " << lastProperPos.toString() << "\n";
		m4sta::mv playerProperPos = m4sta::g0 * X.getT() + m4sta::g1 * X.getX() + m4sta::g2 * X.getY() + m4sta::g3 * X.getZ();
		std::cout << "player proper position   = " << playerProperPos.toString() << "\n";
		m4sta::mv properVelocity = (playerProperPos - lastProperPos);
		std::cout << "player proper velocity   = " << properVelocity.toString() << "\n";
		m4sta::mv relativeVelocity = (properVelocity ^ g0) / (m4sta::sp(properVelocity, m4sta::g0));
		std::cout << "player relative velocity = " << relativeVelocity.toString() << "\n";
		

		// I cannot verify above but the lorentz factor here is finally correct
		// HOWEVER it is only because I switcheroo'd the "dt/dtau" term to be "dtau/dt" 
		// which is obviously because the numbers (player's velocity) is in the player's frame
		// and the formulas in hestenes are for going from a "reference frame" to a particle's frame
		// not the other way around. D'oh!
		m4sta::mv timedilationfactor = (playerProperPos.get_g0() - lastProperPos.get_g0()) / (dt);
		std::cout << "Lorentz factor		   = " << timedilationfactor.toString_f() << "\n";
		


		std::cout << "\n";
		*/

	}
	m4sta::mv RelativityApp::commutatorProduct(m4sta::mv& a, m4sta::mv& b) {
		return (0.5) * (a * b - b * a);
	}

}