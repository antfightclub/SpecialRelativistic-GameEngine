#include "relativity_app.hpp"

// Application
#include "mve_camera.hpp"
#include "systems/lattice_wireframe_system.hpp"
#include "systems/sr_render_system.hpp"
#include "systems/point_light_system.hpp"
#include "mve_buffer.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "entity/object.hpp"
#include "entity/timeclock.hpp"
#include "entity/gravity_source.hpp"
#include "spacetimealgebra/mve_matrix_ops.hpp"

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
#include <math.h> //modf

using namespace m4sta;

namespace mve {

	RelativityApp::RelativityApp() {
		// Initialization: Allocate a descriptor pool for the main rendering system and one for DearImGui.
		globalPool = MveDescriptorPool::Builder(mveDevice)
			.setMaxSets(MveSwapChain::MAX_FRAMES_IN_FLIGHT * 2)
			.addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, MveSwapChain::MAX_FRAMES_IN_FLIGHT) // GlobalUBO
			.addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, MveSwapChain::MAX_FRAMES_IN_FLIGHT) // LatticeUBO
			.addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, MveSwapChain::MAX_FRAMES_IN_FLIGHT) // SpecialRelativityUBO
			.addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, MveSwapChain::MAX_FRAMES_IN_FLIGHT) // PointLightUBO (time clocks)
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
		PointLightSystem pointLightSystem{ mveDevice, mveRenderer.getSwapChainRenderPass(), globalSetLayout->getDescriptorSetLayout() };

		MveCamera camera{};		
		glm::mat4 cameraView{ 1.0 }; // This will be updated later in the update loop
		
		double G = 6.67430e-11; // Gravitational constant
		//double massOfGravitationalSource = 100000;
		//double dist = 5.0;
		double massMainBody = 5.972e6;  // kilograms
		double diameterMainBody = 12756.0; // kilometers
		double heightOfOrbit = 40000; // kilometers
		double radiusOfOrbit = (diameterMainBody/2.0) + heightOfOrbit; // kilometers
		double orbitalVelocity = 7784.34; // meters per second

		diameterMainBody /= 299792458;
		heightOfOrbit /= 299792458;
		radiusOfOrbit /= 299792458;
		orbitalVelocity /= 299792458;

		std::cout << "Diameter of main body : " << diameterMainBody << std::endl;
		std::cout << "Height of orbit       : " << heightOfOrbit << std::endl;
		std::cout << "Radius of orbit       : " << radiusOfOrbit << std::endl;
		std::cout << "Orbital velocity      : " << orbitalVelocity << std::endl;

		// Nah this shit don+t work

		auto viewerObject = MveGameObject::createGameObject(); // Game object to hold camera position
		mv initialPosition{};
		//initialPosition.set_g0(1.0);
		mv initialRapidity{};
		//initialVelocity.set_g0(1.0);
		//double initialVelMagnitude = 0.11;//(std::sqrt(G * (massMainBody * (5.0*299792458)) / (5.0* 299792458)));
		//std::cout << "initial vel magnitude = " << initialVelMagnitude << std::endl;
		//double initialRapMagnitude = atanh(initialVelMagnitude);
		//std::cout << "initial rap magnitude = " << initialRapMagnitude << std::endl;
		//initialRapidity.set_g1(-initialRapMagnitude);
		

		//initialPosition = initialPosition * g0;
		//initialVelocity = initialVelocity * g0;

		//std::cout << initialPosition.toString() << std::endl;
		//std::cout << initialRapidity.toString() << std::endl;

		Player player{ mveWindow , viewerObject, initialPosition, initialRapidity }; // Game player

		//std::cout << std::boolalpha << std::is_move_assignable<vector> << std::cout;

		/*
		float scale = 1.24f;
		float offset = 5.0f;
		int Num = 3;
		std::vector<TimeClock> timeClocks;
		for (int i = -Num; i < Num+1; i++) {
			for (int j = -Num; j < Num+1; j++) {
				for (int k = -Num; k < Num+1; k++) {
					auto timeclockObject = MveGameObject::makePointLight(1.f); // Time clock game objct
					float timeclockColor[3] = { ((double)rand()) / RAND_MAX, ((double)rand()) / RAND_MAX , ((double)rand()) / RAND_MAX };
					float timeclockPosition[3] = { ((float)i+0.5)*scale, ((float)j+0.5)*scale, ((float)k+0.5)*scale+offset };
					TimeClock timeclock{ mveWindow, timeclockObject, timeclockColor, 1.0, timeclockPosition[0] * m4sta::g1 + timeclockPosition[1] * m4sta::g2 + timeclockPosition[2] * m4sta::g3 };
					timeClocks.push_back(timeclock);
					timeclockObject.transform.translation = glm::vec3{ timeclockPosition[0], timeclockPosition[1], timeclockPosition[2] };
					gameObjects.emplace(timeclockObject.getId(), std::move(timeclockObject));
				}
			}
		}
		*/
		
		/*
		float scale = 0.5f;
		float offset = 4.f;
		int Num = 10;
		std::vector<TimeClock> timeClocks;
		for (int i = -Num; i < Num + 1; i++) {
			for (int j = -Num; j < Num + 1; j++) {
				auto timeclockObject = MveGameObject::makePointLight(1.f); // Time clock game objct
				float timeclockColor[3] = { ((double)rand()) / RAND_MAX, ((double)rand()) / RAND_MAX , ((double)rand()) / RAND_MAX };
				float timeclockPosition[3] = {((float)i ) * scale, ((float)j) * scale, 5.f };
				TimeClock timeclock{ mveWindow, timeclockObject, timeclockColor, 1.0, timeclockPosition[0] * m4sta::g1 + timeclockPosition[1] * m4sta::g2 + timeclockPosition[2] * m4sta::g3 };
				timeClocks.push_back(timeclock);
				timeclockObject.transform.translation = glm::vec3{ timeclockPosition[0], timeclockPosition[1], timeclockPosition[2] };
				gameObjects.emplace(timeclockObject.getId(), std::move(timeclockObject));
				//std::cout << "i = " << i << " j = " << j << " k = " << k << "\n";
				//std::cout << "amount of gameobjects = " << gameObjects.size() << "\n";
			}
		}*/

		/*
		float scale = 0.5f;
		float offset = 4.f;
		int Num = 10;
		std::vector<TimeClock> timeClocks;
		for (int i = -Num; i < Num + 1; i++) {
			for (int j = -Num; j < Num + 1; j++) {
				auto timeclockObject = MveGameObject::makePointLight(1.f); // Time clock game objct
				float timeclockColor[3] = { ((double)rand()) / RAND_MAX, ((double)rand()) / RAND_MAX , ((double)rand()) / RAND_MAX };
				float timeclockPosition[3] = { ((float)i) * scale, 1.f , ((float)j) * scale};
				TimeClock timeclock{ mveWindow, timeclockObject, timeclockColor, 1.0, timeclockPosition[0] * m4sta::g1 + timeclockPosition[1] * m4sta::g2 + timeclockPosition[2] * m4sta::g3 };
				timeClocks.push_back(timeclock);
				timeclockObject.transform.translation = glm::vec3{ timeclockPosition[0], timeclockPosition[1], timeclockPosition[2] };
				gameObjects.emplace(timeclockObject.getId(), std::move(timeclockObject));
				//std::cout << "i = " << i << " j = " << j << " k = " << k << "\n";
				//std::cout << "amount of gameobjects = " << gameObjects.size() << "\n";
			}
		}*/


		//std::cout << "timeClocks.size() = " << timeClocks.size() << "\n";
		//auto timeclockObject = MveGameObject::makePointLight(); // Time clock game objct
		//float timeclockColor[3] = { 1.f, 1.f, 1.f };
		//float timeclockPosition[3] = { 1.f, 1.f, 1.f };
		//TimeClock timeclock{ mveWindow, timeclockObject, timeclockColor, 1.0, timeclockPosition[0] * m4sta::g1 + timeclockPosition[1] * m4sta::g2 + timeclockPosition[2] * m4sta::g3 };
		//timeclockObject.transform.translation = glm::vec3{ timeclockPosition[0], timeclockPosition[1], timeclockPosition[2]};
		//gameObjects.emplace(timeclockObject.getId(), std::move(timeclockObject));

		// Old Enemy class
		//std::shared_ptr<MveModel> cubeModel = MveModel::createModelFromFile(mveDevice, "./models/gay_cube.obj");
		//auto enemyObject = MveGameObject::createGameObject(); // The enemy's game object
		//enemyObject.model = nullptr;//cubeModel;
		//Enemy enemy{ mveWindow, enemyObject, Math::Vector4D{0.0, 3.0, 0.0, 4.0}, Math::EntityState{} };
		//enemyObject.transform.translation = { 3.0f, 0.0f, 4.0f };
		//gameObjects.emplace(enemyObject.getId(), std::move(enemyObject));

		// New TestObject class for testing polygon rendering (and getting rid of quaternions)
		m4sta::mv testObjectInitialPosition = 3.0 * g1 + 4.0 * g3;
		std::shared_ptr<MveModel> cubeModel = MveModel::createModelFromFile(mveDevice, "./models/gay_cube.obj");
		auto testObjectGO = MveGameObject::createGameObject();
		testObjectGO.model = cubeModel;
		TestObject testObject{ mveWindow, testObjectGO, testObjectInitialPosition };
		testObjectGO.transform.translation = { testObjectInitialPosition.get_g1(), testObjectInitialPosition.get_g2(), testObjectInitialPosition.get_g3()};
		gameObjects.emplace(testObjectGO.getId(), std::move(testObjectGO));


		// Spawn timeclocks as a trail
		std::vector<TimeClock> timeClocks;
		double accumulator = 0.0;
		bool spawnTimeClocks = false;

		//std::shared_ptr<MveModel> sphereModel = MveModel::createModelFromFile(mveDevice, "./models/colored_sphere.obj");
		auto massiveObject = MveGameObject::makePointLight();
		float massiveObjColor[3] = { 0.f, 0.f, 1.f };
		float massiveObjPosition[3] = { 0.f, 0.f, 5.f };
		//massiveObject.model = sphereModel;
		//double mass = 1000000;
		TimeClock timeclock{ mveWindow, massiveObject, massiveObjColor, 1.0, massiveObjPosition[0] * g1 + massiveObjPosition[1] * g2 + massiveObjPosition[2] * g3 };
		massiveObject.transform.translation = { 0.0f, 0.0f, 5.0f };
		timeClocks.push_back(timeclock);

		mv gravInitialPos{};
		mv gravInitialRap{};
		//gravInitialRap.set_g3(0.2);
		gravInitialPos.set_g3(5.0);
		//gravInitialPos

		GravitySource gravitySource{ mveWindow, massiveObject, massMainBody, gravInitialPos, gravInitialRap };

	
		gameObjects.emplace(massiveObject.getId(), std::move(massiveObject));
		


		// Used to have the keyboard input controller rrrrdefined here
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

			camera.setPerspectiveProjection(glm::radians(100.0f), aspect, 0.01f, 1000.0f);

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
				gravitySource.Action(mveWindow.getGLFWwindow(), dt);
				//struct GravitationData {
				//	double G;
				//	double massOfObject;
				//	m4sta::mv rapidityOfObject;
				//	m4sta::mv positionOfObject;
				//};
				GravitationData g{};
				g.G = G; //6.67430e-11; // Defined above somewhere
				g.massOfObject = massMainBody;
				g.rapidityOfObject = gravitySource.rapidity;
				g.positionOfObject = gravitySource.position;

				player.Action(mveWindow.getGLFWwindow(), dt, g);
				testObject.Action(mveWindow.getGLFWwindow(), dt);
				//enemy.Action(mveWindow.getGLFWwindow(), dt);
				
				//for (int i = 0; i < timeClocks.size(); i++) {
				//	timeClocks[i].Action(mveWindow.getGLFWwindow(), dt);
				//}
				

				// Should get a GLM rotation matrix directly instead of this, but will require a rewrite of Math:: namespace
				Math::Quaternion playerOrientation = player.quaternion;
				
				float playerPos[3] = { (float)player.P.position.get_g1(), (float)player.P.position.get_g2(), (float)player.P.position.get_g3() };

				// Establish camera view matrix
				glm::vec3 playerPosition = glm::vec3{ playerPos[0], playerPos[1], playerPos[2] };
				glm::quat orientation = glm::quat{ (float)playerOrientation.t, (float)playerOrientation.x, (float)playerOrientation.y, (float)playerOrientation.z };				
				glm::mat4 rotate = glm::toMat4(orientation); 
				glm::mat4 translate = glm::mat4(1.0f);
				//translate = glm::translate(translate, playerPos);
				
				// NOTE: Currently, we do *not* translate the camera view matrix.
				// If we did, we would inadvertedly make sure the Lorentz trans-
				// formation is centered in the origin of the grid.

				cameraView = glm::inverse(translate * rotate);
				viewerObject.transform.translation = playerPosition;
				
				camera.setView(cameraView); // Sets the camera view matrix

				glm::mat4 invView = glm::inverse(cameraView); // Inverse camera view matrix

				// Update buffer holding GlobalUbo
				GlobalUbo globalUbo{};
				globalUbo.projection = camera.getProjection();
				globalUbo.view = camera.getView();
				globalUbo.inverseView = invView;
				globalUbo.Lorentz = LorentzMatrixFromRapidity(player.P.rapidity);
				globalUbo.ambientLightColor = { 1.f, 1.f, 1.f, .02f };
				globalUbo.observerPosition = { playerPos[0], playerPos[1], playerPos[2], 1.0};
				globalUboBuffers[frameIndex]->writeToBuffer(&globalUbo);
				globalUboBuffers[frameIndex]->flush();

				
				// Xp = player's position in the background frame
				glm::vec3 Xp = glm::vec3{ playerPos[0], playerPos[1], playerPos[2]};

				// Xo = displacement of lattice by Lattice Unit N/L to keep it centered on the player in the vertex shader
				int xo = int(int(Xp.x / (lattice.latticeUnit)) * (lattice.latticeUnit));
				int yo = int(int(Xp.y / (lattice.latticeUnit)) * (lattice.latticeUnit));
				int zo = int(int(Xp.z / (lattice.latticeUnit)) * (lattice.latticeUnit));
				

				//Math::Vector4D X{};
				//Math::Vector4D U{};
				//X.setT(player.P.position.get_g0());
				//X.setX(player.P.position.get_g1());
				//X.setY(player.P.position.get_g2());
				//X.setZ(player.P.position.get_g3());
				//
				//U.setT(cosh(norm(player.P.rapidity)));
				//U.setX(player.P.rapidity.get_g1());
				//U.setY(player.P.rapidity.get_g2());
				//U.setZ(player.P.rapidity.get_g3());
				

				//Math::Matrix44 L{};	
				//L = Math::Matrix44::Lorentz(U); // Lorentz boost matrix : Bg frame -> Player frame
				//glm::mat4 lorentz = L.toGLM();			 // .toGLM() transposes the matrix to conform to GLSL conventions
				//				Math::Matrix44 LL{};
				//LL = Math::Matrix44::Lorentz(-U);	// Not sure how to use yet; but it transforms from the player's frame of reference to the background frame of reference.
				//glm::mat4 invLorenz = LL.toGLM();
				//
				//glm::mat4 anotherLorentz = LorentzMatrixFromRapidity(player.P.rapidity);
				//glm::mat4 anoteherLLorentz = LorentzMatrixFromRapidity(-player.P.rapidity);
				// Update buffer holding LatticeUbo
				LatticeUbo latticeUbo{};
				latticeUbo.Xp = glm::vec3{ Xp.x, Xp.y, Xp.z};
				latticeUbo.Xo = glm::vec3{ xo,   yo,   zo };
				latticeUboBuffers[frameIndex]->writeToBuffer(&latticeUbo);
				latticeUboBuffers[frameIndex]->flush();
				latticeUboBuffer.flushIndex(frameIndex);

				//EnemyDrawData eDrawData = enemy.getDrawData(X, L, LL);
				//
				//Math::Vector4D gSrcX{};
				//gSrcX.setT(gravitySource.position.get_g0());
				//gSrcX.setX(gravitySource.position.get_g1());
				//gSrcX.setY(gravitySource.position.get_g2());
				//gSrcX.setZ(gravitySource.position.get_g3());
				//
				//Math::Vector4D dX = gSrcX - X;
				//dX.setT(-dX.length()); // spacetime interval
				//Math::Vector4D negdX = -dX;
				//Math::Vector4D x_p = Math::Matrix44::Lorentz(eDrawData.U).getTransform(negdX);
				//
				//glm::vec4 xp = glm::vec4{ (float)x_p.getX(), (float)x_p.getY(), (float)x_p.getZ(), (float)x_p.getT() };
				//
				//Math::Vector4D dee_X = L.getTransform(dX);
				//glm::vec4 dX_playerframe = glm::vec4{ (float)dee_X.getX(), (float)dee_X.getY(), (float)dee_X.getZ(), 0.f };
				//
				//// LL   -    player frame to background frame, then background frame to enemy frame
				//glm::mat4 L_p2b_b2e = (Math::Matrix44::Lorentz(eDrawData.U) * LL).toGLM();
				//
				//// L    -    enemy to player frame
				//glm::mat4 L_e2p = (L * Math::Matrix44::Lorentz(-eDrawData.U)).toGLM();
				//
				//glm::quat enemyOrientation = glm::quat{ (float)eDrawData.quaternion.t, (float)eDrawData.quaternion.x, (float)eDrawData.quaternion.y, (float)eDrawData.quaternion.z };
				//
				//SpecialRelativityUbo srUbo{};
				//srUbo.Lorentz = L_e2p;
				//srUbo.Lorentz_p2e = L_p2b_b2e;
				//srUbo.Rotate = glm::toMat4(enemyOrientation);
				//srUbo.dX = dX_playerframe;
				//srUbo.xp = xp;
				

				//MvePhaseSpace gSrcDrawData = gravitySource.getDrawData(player.P.position);

				//glm::vec4 dx_playerframe = glm::vec4{}

				ObjectDrawData objDrawData = testObject.getDrawData(player.P.position);
				// Just fixed a NaN, it seems that the calculated rapidity is NaN if the change in position between consecutive worldline entries is zero
				m4sta::mv objPos = objDrawData.phaseSpace.position;
				m4sta::mv objRap = objDrawData.phaseSpace.rapidity;
				
				
				glm::mat4 objL{1.0};
				glm::mat4 objLL{1.0};

				objL = LorentzMatrixFromRapidity(objDrawData.phaseSpace.rapidity);				// Background frame to object frame
				objLL = LorentzMatrixFromRapidity(-objDrawData.phaseSpace.rapidity);			// Object frame     to background frame

				glm::mat4 playerL = LorentzMatrixFromRapidity(player.P.rapidity);				// Background frame to player frame
				glm::mat4 playerLL = LorentzMatrixFromRapidity(-player.P.rapidity);				// Player frame     to background frame
				
				glm::mat4 L_o2p = (playerL * objLL);
				glm::mat4 L_p2o = (objL * playerLL);

				// Need to find out where the object is *in the player frame*.
				// First find object's position in background frame. 
				// Then find player's position in background frame.
				m4sta::mv objectPosition = objDrawData.phaseSpace.position;
				m4sta::mv playerPosMV = player.P.position;

				m4sta::mv diffPosition{};
				
				//diffPosition.set_g0(objectPosition.get_g0() + playerPosMV.get_g0());
				diffPosition.set_g1(objectPosition.get_g1() - playerPosMV.get_g1());
				diffPosition.set_g2(objectPosition.get_g2() - playerPosMV.get_g2());
				diffPosition.set_g3(objectPosition.get_g3() - playerPosMV.get_g3());
				
				// Spacetime interval
				diffPosition.set_g0(-std::sqrt(
					diffPosition.get_g1()* diffPosition.get_g1()
					+ diffPosition.get_g2() * diffPosition.get_g2()
					+ diffPosition.get_g3() * diffPosition.get_g3()));
				
				
				m4sta::mv x_p = transformWithLorentzMatrix(objL, -diffPosition);

				m4sta::mv xp_playerframe = transformWithLorentzMatrix(playerL, diffPosition);
				xp_playerframe.set_g0(0.0);

		
				std::cout << "objectPos      : " << objectPosition.toString() << std::endl;
				std::cout << "playerPos      : " << playerPosMV.toString() << std::endl;
				std::cout << "diff  Pos      : " << diffPosition.toString() << std::endl;
				std::cout << "x_p            : " << x_p.toString() << std::endl;
				std::cout << "xp_playerframe : " << xp_playerframe.toString() << std::endl;

				std::cout << std::endl;

				// Might actually need a second matrix... I think that 
				// the LSBattle "L" is "enemy to player"
				// and the "LL" is the "player to enemy"
				SpecialRelativityUbo srUbo{};
				srUbo.Lorentz_p2o = L_o2p;
				srUbo.Lorentz_p2o = L_p2o;
				srUbo.Rotate = glm::mat4{1.0};
				srUbo.dX = glm::vec4{xp_playerframe.get_g1(), xp_playerframe.get_g1(), xp_playerframe.get_g3(), xp_playerframe.get_g0()};
				srUbo.xp = glm::vec4{x_p.get_g1(), x_p.get_g2(), x_p.get_g3(), x_p.get_g0()};
				specialRelativityUboBuffers[frameIndex]->writeToBuffer(&srUbo);
				specialRelativityUboBuffers[frameIndex]->flush();
				specialRelativityUboBuffer.flushIndex(frameIndex);


				accumulator += dt;
				if (accumulator >= 1.0) {
					// Spawn timeclock I guess
					if (spawnTimeClocks == true) {
						//auto timeclockObject = MveGameObject::makePointLight(1.f); // Time clock game objct
						//float timeclockColor[3] = { ((double)rand()) / RAND_MAX, ((double)rand()) / RAND_MAX , ((double)rand()) / RAND_MAX };
						//float timeclockPosition[3] = { ((float)i) * scale, ((float)j) * scale, 5.f };
						//TimeClock timeclock{ mveWindow, timeclockObject, timeclockColor, 1.0, timeclockPosition[0] * m4sta::g1 + timeclockPosition[1] * m4sta::g2 + timeclockPosition[2] * m4sta::g3 };
						//timeClocks.push_back(timeclock);
						//timeclockObject.transform.translation = glm::vec3{ timeclockPosition[0], timeclockPosition[1], timeclockPosition[2] };
						//gameObjects.emplace(timeclockObject.getId(), std::move(timeclockObject));

						auto timeclockObject = MveGameObject::makePointLight(1.f);
						float timeclockColor[3] = { 1.0, 1.0, 1.0 };
						float timeclockPosition[3] = { (float)player.P.position.get_g1(), (float)player.P.position.get_g2(), (float)player.P.position.get_g3() };
						TimeClock timeclock{ mveWindow, timeclockObject, timeclockColor, 1.0, timeclockPosition[0] * m4sta::g1 + timeclockPosition[1] * m4sta::g2 + timeclockPosition[2] * m4sta::g3 };
						timeClocks.push_back(timeclock);
						timeclockObject.transform.translation = glm::vec3{ timeclockPosition[0], timeclockPosition[1], timeclockPosition[2] };
						gameObjects.emplace(timeclockObject.getId(), std::move(timeclockObject));

					}
					accumulator = 0.0;
				}

				
				//mv observerPosition = player.P.position;
				
				
				std::vector<size_t> worldLineSize;
				std::vector<TimeClockDrawData> clocksDrawData;
				auto before = std::chrono::high_resolution_clock::now();
				for (auto timeclock : timeClocks) {
					TimeClockDrawData cDrawData = timeclock.getDrawData(player.P.position);
					size_t worldlineEntryAmount = timeclock.getWorldlineEntryAmount();
					clocksDrawData.push_back(cDrawData);
					worldLineSize.push_back(worldlineEntryAmount);
				}
				auto after = std::chrono::high_resolution_clock::now();
				double timeAmount = std::chrono::duration<double, std::chrono::milliseconds::period>(after - before).count();

				for (int i = 0; i < timeClocks.size(); i++) {
					MveGameObject::id_t id = timeClocks[i].getGameObjectID();
					auto& obj = gameObjects.at(id);
					double t = clocksDrawData[i].phaseSpace.position.get_g0();
					if (fmod(t, 4) >= 2.0) {
						obj.color = glm::vec3{ clocksDrawData[i].color[0], clocksDrawData[i].color[1], clocksDrawData[i].color[2] };
						obj.transform.scale.x = 0.2f;
					}
					else if (fmod(t, 4) <= 2.0) {
						//obj.color = glm::vec3{ 0.1*clocksDrawData[i].color[0], 0.1*clocksDrawData[i].color[1], 0.1*clocksDrawData[i].color[2] };
						//obj.transform.scale.x = 0.1;
						obj.color = glm::vec3{ clocksDrawData[i].color[0], clocksDrawData[i].color[1], clocksDrawData[i].color[2] };
						obj.transform.scale.x = 0.19f;
					}
				}
				

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

					double G = 1;		// Gravitational constant
					double M = 100000;	// kilograms
					mv position = 1.0 * g0 ^ g1;
					
					mv playerPos = player.P.position;
					mv xarrow = playerPos * g0;
					xarrow.set_scalar(0.0);
					double ct = (player.P.position * g0).get_scalar();

					mv rhat = xarrow - position;
					double r = norm(rhat);
					rhat = unit(rhat);

					mv Narrow = - ((G* M)/(r*r)) * 1 * rhat;

					//ImGui::Text("Narrow:");
					//ImGui::Text(Narrow.c_str());

					

					/*
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
					*/

					ImGui::Text("Player Position:");
					ImGui::Text(player.P.position.c_str());
					ImGui::Text("Player relative position:");
					ImGui::Text((player.P.position * g0).c_str());
					ImGui::Text("Player Rapidity:");
					ImGui::Text(player.P.rapidity.c_str());
					ImGui::Text("Player Velocity:");
					mv velocity = player.P.rapidity;
					velocity = unit(velocity);
					double magnitude = tanh(norm(player.P.rapidity));
					velocity *= magnitude;
					velocity.set_g0(cosh(norm(player.P.rapidity)));
					ImGui::Text(velocity.c_str());
					//ImGui::Text("Player relative velocity:");
					//ImGui::Text((velocity * g0).c_str());
					//
					//
					//double rest_mass = 100; // I'll just say this is in units kg
					//mv momentum = rest_mass * velocity;
					//mv angular_momentum_bivector = player.P.position ^ momentum;
					//
					//ImGui::Text("Player rest mass: %.3f", rest_mass);
					//ImGui::Text("Player momentum:");
					//ImGui::Text(momentum.c_str());
					//ImGui::Text("Player relative momentum:");
					//ImGui::Text((momentum * g0).c_str());
					//ImGui::Text("Player momentum squared:");
					//ImGui::Text((momentum * momentum).c_str());
					//
					//ImGui::Text("M :");
					//ImGui::Text(angular_momentum_bivector.c_str());
					//
					//mv parrow = (momentum * g0);
					//parrow.set_scalar(0.0);
					//
					//mv xarrow = (player.P.position * g0);
					//xarrow.set_scalar(0.0);
					//double ct = (player.P.position * g0).get_scalar();
					//double Eoverc = (momentum * g0).get_scalar();
					//
					//mv varrow = (velocity * g0);
					//
					//mv Narrow = (ct * parrow) - (Eoverc * xarrow);
					//
					//// I(a x b) = (a ^ b)
					//// (a x b) = I(a ^ b)		????
					//
					//mv Larrow = I*(xarrow ^ parrow);
					//// therefore M becomes
					//// M = -c * Narrow - Larrow
					//mv angular_momentum_bivector_2 = -1.0 * Narrow - Larrow*I;
					//ImGui::Text("M 2 : ");
					//ImGui::Text(angular_momentum_bivector_2.c_str());
					//
					//ImGui::Text("Narrow: ");
					//ImGui::Text(Narrow.c_str());


					// hmmm.. for some reason they are different. 
					// angular momentum bivector 
					// has components g01, g02, g03, g12, g23, g31
					// angular momentum bivector 2 
					// has components g01, g02, g03 only?
					// Not sure which one is "correct"

					double magRap = norm(player.P.rapidity);
					// Lorentz 
					double g = cosh(magRap); //player.P.U.getGamma(); // Lorentz Factor
					double u = tanh(magRap);//std::sqrt(1.0 - (1.0 / (g * g))); // Fraction of c
					double v = Math::c * u;

					ImGui::NewLine();
					ImGui::Text("speed: %f [m/s]", v);
					ImGui::Text("c = %f", u);
					ImGui::Text("Lorentz factor: %.3f", g);
					ImGui::NewLine();
					ImGui::Text("Proper Time: %.3f [s]", frameTime);
					ImGui::Text("World  Time: %.3f [s]", player.P.position.get_g0());

					ImGui::NewLine();
					ImGui::Checkbox("show/hide lattice", &renderLattice);
					ImGui::Checkbox("spawn/do not spawn timeclocks", &spawnTimeClocks);
					ImGui::Text("Amount of timeclocks = %u", timeClocks.size());
					/*
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
					*/
				}
				ImGui::End();
				if (ImGui::Begin("Spacetime Algebra", &sta_open)) {
					//ImGui::Text("Player position: ");
					//ImGui::Text(playerPos.c_str_f());
					//ImGui::Text("Player velocity: ");
					//ImGui::Text(playerVel.c_str_f());
					//ImGui::Text("Split of velocity: ");
					//ImGui::Text(splitVel.c_str_f());

					static float theta;
					static float phi;

					static float vvec[4]{};
					static float mvec[4]{};
					static float nvec[4]{};
					ImGui::InputFloat("Theta", &theta);
					ImGui::InputFloat("Phi", &phi);

					ImGui::InputFloat4("v", vvec);
					ImGui::InputFloat4("m", mvec);
					ImGui::InputFloat4("n", nvec);

					mv v = vvec[0] * g0 - vvec[1] * g1 - vvec[2] * g2 - vvec[3] * g3;
					mv m = mvec[0] * g0 - mvec[1] * g1 - mvec[2] * g2 - mvec[3] * g3;
					mv n = nvec[0] * g0 - nvec[1] * g1 - nvec[2] * g2 - nvec[3] * g3;

					v = unit(v);
					m = unit(m);
					n = unit(n);

					mv v_rel = g0 ^ v;
					mv m_rel = g0 ^ m;
					mv n_rel = g0 ^ n;
					mv v_sqrd = v * v;
					mv m_x_n = m ^ n;
					// Unsure about this one
					mv m_x_n_sqrd = -((mvec[0] * nvec[1] - mvec[1] * nvec[0]) * (mvec[0] * nvec[1] - mvec[1] * nvec[0])
						+ (mvec[1] * nvec[2] + mvec[2] * nvec[1]) * (mvec[1] * nvec[2] + mvec[2] * nvec[1])
						+ (mvec[2] * nvec[3] + mvec[3] * nvec[2]) * (mvec[2] * nvec[3] + mvec[3] * nvec[2]));
					
					mv ev{};
					if (v_sqrd.get_scalar() >= 0.00001) {
						ev = div(v_rel, std::sqrt(v_sqrd.get_scalar()));
					}
					else if (v_sqrd.get_scalar() <= 0.00001) {
						ev = div(v_rel, std::sqrt(-v_sqrd.get_scalar()));
					}
					else {
						
					}

					//mv ev = div(v_rel, std::sqrt(v_sqrd.get_scalar()));
					mv I2 = div(m_x_n, std::sqrt(-m_x_n_sqrd.get_scalar()));

					
					ImGui::Text("v         : "); ImGui::SameLine(); ImGui::Text(v.c_str());
					ImGui::Text("v_rel     : "); ImGui::SameLine(); ImGui::Text(v_rel.c_str());
					ImGui::Text("m         : "); ImGui::SameLine(); ImGui::Text(m.c_str());
					ImGui::Text("m_rel     : "); ImGui::SameLine(); ImGui::Text(m_rel.c_str());
					ImGui::Text("n         : "); ImGui::SameLine(); ImGui::Text(n.c_str());
					ImGui::Text("n_rel     : "); ImGui::SameLine(); ImGui::Text(n_rel.c_str());
					ImGui::NewLine();
					ImGui::Text("m x n     : "); ImGui::SameLine(); ImGui::Text(m_x_n.c_str());
					ImGui::Text("v_sqrd    : "); ImGui::SameLine(); ImGui::Text(v_sqrd.c_str());
					ImGui::Text("(m x n)^2 : "); ImGui::SameLine(); ImGui::Text(m_x_n_sqrd.c_str());
					ImGui::NewLine();
					ImGui::Text("ev        : "); ImGui::SameLine(); ImGui::Text(ev.c_str());
					ImGui::Text("I2        : "); ImGui::SameLine(); ImGui::Text(I2.c_str());
					ImGui::Text("ev^2      : "); ImGui::SameLine(); ImGui::Text((ev*ev).c_str());
					ImGui::Text("I2^2      : "); ImGui::SameLine(); ImGui::Text((I2*I2).c_str());
					
					mv exp_ev = exp((theta / 2) * ev);
					mv exp_I2 = exp((phi / 2) * I2);

					static float xvec[4]{};
					static float yvec[4]{};
					ImGui::InputFloat4("x", xvec);
					ImGui::InputFloat4("y", yvec);
					mv x = xvec[0] * g0 - xvec[1] * g1 - xvec[2] * g2 - xvec[3] * g3;
					mv y = yvec[0] * g0 - yvec[1] * g1 - yvec[2] * g2 - yvec[3] * g3;

					x = unit(x);
					y = unit(y);

					mv xprime = exp_ev * (x) * (~exp_ev);
					mv yprime = exp_I2 * (y) * (~exp_I2);
					
					ImGui::Text("x         : "); ImGui::SameLine(); ImGui::Text(x.c_str());
					ImGui::Text("y         : "); ImGui::SameLine(); ImGui::Text(y.c_str());
					ImGui::Text("x'        : "); ImGui::SameLine(); ImGui::Text(xprime.c_str());
					ImGui::Text("y'        : "); ImGui::SameLine(); ImGui::Text(yprime.c_str());

					mv numerator = x ^ xprime;
					mv denominator = (x ^ xprime) * (x ^ xprime);
					if (denominator.get_scalar() >= 0.00001) {
						denominator = std::sqrt(denominator.get_scalar());
					}
					mv biv = div(numerator, denominator.get_scalar());
					mv Lhat = exp(-(theta / 2.0) * biv);

					ImGui::Text("Lhat     : "); ImGui::SameLine(); ImGui::Text(Lhat.c_str());

					mv xprimetwo = (~Lhat) * x * Lhat;
					ImGui::Text("~Lhat * x * Lhat : "); ImGui::SameLine(); ImGui::Text(xprimetwo.c_str());
					
					/*static float magnitude_v = 0.0;
					ImGui::InputFloat("v magnitude", &magnitude_v, -1.0f, 1.0f);
					static float magnitude_u = 0.0;
					ImGui::InputFloat("u magnitude", &magnitude_u, -1.0f, 1.0f);

					static float v_dir[3] = { 0.0f, 1.0f, 0.0f };
					static float u_dir[3] = { 0.0f, 1.0f, 0.0f };

					ImGui::SliderFloat3("v dir", v_dir, -2.0f, 2.f);
					ImGui::SliderFloat3("u dir", u_dir, -2.0f, 2.f);

					static float v_g0{};
					static float u_g0{};

					ImGui::InputFloat("v time", &v_g0);
					ImGui::InputFloat("u time", &u_g0);

					// The most interesting thing I found out today was that
					// The velocity addition *only works* if using bivectors
					// in the STA. Using set_g1 instead breaks it!
					// Perhaps I've been thinking about this all wrong. I think
					// maybe velocities need to be w.r.t. the unit timelike g0!
					// Worldlines are still events in spacetime, but if I want 
					// to represent anything, it's gotta be the spacetime split!

					// So, what if I instead do have a velocity using g1, g2, g3,
					// but then do a spacetime split afterwards?

					mv v;
					v.set_g0(v_g0);
					v.set_g1(v_dir[0]);
					v.set_g2(v_dir[1]);
					v.set_g3(v_dir[2]);
					mv u;
					u.set_g0(u_g0);
					u.set_g1(u_dir[0]);
					u.set_g2(u_dir[1]);
					u.set_g3(u_dir[2]);

					v = unit(v);
					u = unit(u);

					v *= magnitude_v;
					u *= magnitude_u;

					mv v_compare = v;
					mv u_compare = u;
					// spacetime split	
					v = v * g0;
					u = u * g0;

					mv finalvel = (v + u) * m4sta::versorInverse(1 + v*u); 

					ImGui::Text("v             : "); ImGui::SameLine(); ImGui::Text(v_compare.c_str());
					ImGui::Text("v*g0          : "); ImGui::SameLine(); ImGui::Text(v.c_str());
					ImGui::Text("u             : "); ImGui::SameLine(); ImGui::Text(u_compare.c_str());
					ImGui::Text("u*g0          : "); ImGui::SameLine(); ImGui::Text(u.c_str());
					ImGui::NewLine();
					ImGui::Text("vel add       : "); ImGui::SameLine(); ImGui::Text(finalvel.c_str());

					double vel_magnitude = norm(finalvel);
					//ImGui::NewLine();
					ImGui::Text("vel magnitude : %.3f", vel_magnitude);

					ImGui::Text("g0 * v * g0   : "); ImGui::SameLine(); ImGui::Text((g0 * v_compare * g0).c_str());
					ImGui::Text("g0 * ~v * g0  : "); ImGui::SameLine(); ImGui::Text((g0 * ~v_compare * g0).c_str());
					*/

					//ImGui::Text("It took %f milliseconds to foliate %u timeclocks.", timeAmount, worldLineSize.size());
					/*
					static ImGuiTableFlags flags = ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable;
					//ImVec2 outer_size = ImVec2(0.0f, TEXT_BASE_HEIGHT * 8);
					if (ImGui::BeginTable("worldline_sizes", 2, flags)) {
						ImGui::TableSetupScrollFreeze(0, 1); // Make top row always visible
						ImGui::TableSetupColumn("TimeClock", ImGuiTableColumnFlags_None);
						ImGui::TableSetupColumn("Size of worldline", ImGuiTableColumnFlags_None);
						ImGui::TableHeadersRow();

						for (int i = 0; i < timeClocks.size(); i++) {
							ImGui::TableNextRow();
							for (int j = 0; j < 2; j++) {
								ImGui::TableSetColumnIndex(j);
								if (j == 0) {
									ImGui::Text("TimeClock #%d", i);
								}
								else if (j == 1) {
									ImGui::Text("%u", worldLineSize[i]);
								}
							}
						}
						
						ImGui::EndTable();
					}*/
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
				pointLightSystem.render(frameInfo, glm::vec3{ playerPos[0], playerPos[1], playerPos[2] });
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
	
	// Important: Make sure A and B only has components in:
	// g10, g20, g30. 
	// This is also the reason why the result is negated in each step.
	mv RelativityApp::p3CrossProduct(m4sta::mv& A, m4sta::mv& B) {
		mv res;
		res.set_g0_g1(-(A.get_g0_g2() * B.get_g0_g3() - A.get_g0_g3() * B.get_g0_g2()));
		res.set_g0_g2(-(A.get_g0_g3() * B.get_g0_g1() - A.get_g0_g1() * B.get_g0_g3()));
		res.set_g0_g3(-(A.get_g0_g1() * B.get_g0_g2() - A.get_g0_g2() * B.get_g0_g1()));
		return res;
	}

}