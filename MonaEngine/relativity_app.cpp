#include "relativity_app.hpp"

#include "keyboard_movement_controller.hpp"
#include "mve_camera.hpp"
#include "systems/lattice_wireframe_system.hpp"
#include "mve_buffer.hpp"
#include "lattice.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm.hpp>
#include <gtc/constants.hpp>

//std
#include <cassert>
#include <chrono>
#include <stdexcept>
#include <array>
#include <iostream>

namespace mve {

	RelativityApp::RelativityApp() {
		globalPool = MveDescriptorPool::Builder(mveDevice)
			.setMaxSets(MveSwapChain::MAX_FRAMES_IN_FLIGHT)
			.addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, MveSwapChain::MAX_FRAMES_IN_FLIGHT)
			.build();

		loadGameObjects();
	}

	RelativityApp::~RelativityApp() {}
	
	void RelativityApp::run() {

		std::cout << "start run!" << std::endl;

		// (I Think) this is buffers for each frame in flight
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
		
		std::cout << "global ubo buffers created!" << std::endl;

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

		std::cout << "lattice ubo buffers created!" << std::endl;

		globalUboBuffer.map();
		latticeUboBuffer.map();

		std::cout << "global and lattice ubo buffers mapped!!" << std::endl;

		auto descriptorSetLayout = MveDescriptorSetLayout::Builder(mveDevice)
			.addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT) // Global Ubo 
			.addBinding(1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT)								 // Lattice Ubo
			.build();
		
		std::cout << "descriptorsetlayout!" << std::endl;

		std::vector<VkDescriptorSet> globalDescriptorSets(MveSwapChain::MAX_FRAMES_IN_FLIGHT);
		for (int i = 0; i < globalDescriptorSets.size(); i++) {
			auto globalBufferInfo = globalUboBuffers[i]->descriptorInfo();
			auto latticeBufferInfo = latticeUboBuffers[i]->descriptorInfo();
			MveDescriptorWriter(*descriptorSetLayout, *globalPool)
				.writeBuffer(0, &globalBufferInfo)
				.writeBuffer(1, &latticeBufferInfo)
				.build(globalDescriptorSets[i]);
		}

		std::cout << "globalDescriptorsets!!" << std::endl;

		LatticeWireframeSystem latticeRenderSystem{ mveDevice, mveRenderer.getSwapChainRenderPass(), descriptorSetLayout->getDescriptorSetLayout() };
		MveCamera camera{};
		camera.setViewDirection(glm::vec3(0.f), glm::vec3(0.5f, 0.f, 1.f));
		camera.setViewTarget(glm::vec3(-1.f, -2.f, -2.f), glm::vec3(0.f, 0.f, 2.5f));

		auto viewerObject = MveGameObject::createGameObject();
		viewerObject.transform.translation.z = -2.5f;
		KeyboardMovementController cameraController{};

		std::cout << "rendersystem and viewer object and cam!" << std::endl;

		auto currentTime = std::chrono::high_resolution_clock::now();
	
		std::cout << "just before while loop!" <<  std::endl;
		while (!mveWindow.shouldClose()) {
			glfwPollEvents();

			std::cout << "start of while loop!!" << std::endl;

			auto newTime = std::chrono::high_resolution_clock::now();
			float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
			
			std::cout << "frameTime = " << frameTime << std::endl;

			cameraController.moveInPlaneXZ(mveWindow.getGLFWwindow(), frameTime, viewerObject);
			camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

			float aspect = mveRenderer.getAspectRatio();

			std::cout << "aspect = " << aspect << std::endl;

			camera.setPerspectiveProjection(glm::radians(50.f), aspect, 0.1f, 100.0f);

			if (auto commandBuffer = mveRenderer.beginFrame()) {
				int frameIndex = mveRenderer.getFrameIndex();
				FrameInfo frameInfo{
					frameIndex,
					frameTime,
					commandBuffer,
					camera,
					globalDescriptorSets[frameIndex],
					gameObjects
				};

				// ***** update
				std::cout << "just before update in while loop!" << std::endl;
				// update global ubo buffer
				GlobalUbo globalUbo{};
				globalUbo.projection = camera.getProjection();
				globalUbo.view = camera.getView();
				globalUbo.inverseView = camera.getInverseView();
				globalUboBuffers[frameIndex]->writeToBuffer(&globalUbo);
				globalUboBuffers[frameIndex]->flush();
				
				// TODO: update lattice ubo buffer
				LatticeUbo latticeUbo{};
				latticeUbo.Xp = camera.getPosition();
				latticeUbo.Xo = glm::vec3{ 0.0f,0.0f,0.0f };
				latticeUbo.Lorentz = glm::mat4{ 1.0f };
				latticeUboBuffers[frameIndex]->writeToBuffer(&latticeUbo);
				latticeUboBuffers[frameIndex]->flush();
				latticeUboBuffer.flushIndex(frameIndex);
				
				std::cout << "just before render in while loop!" << std::endl;

				// Render
				mveRenderer.beginSwapChainRenderPass(commandBuffer);
				
				// order matters (if semitransparency is involved)
				latticeRenderSystem.renderWireframe(frameInfo);

				mveRenderer.endSwapChainRenderPass(commandBuffer);
				mveRenderer.endFrame();				
			}
		}


		vkDeviceWaitIdle(mveDevice.device());
	}

	void RelativityApp::loadGameObjects() {
		std::cout << "loadGameObjects called!" << '\n';
		// generate lattice
		Lattice lattice{100, 30, 5, 1, 1.0};
		std::cout << "Calling makeLattice..." << '\n';
		
		std::cout << "Getting vertices..." << '\n';
		auto vertices = lattice.getVertices();
		
		std::cout << "creating model from std vectors..." << '\n';
		std::shared_ptr<MveModel> mveModel = MveModel::createModelFromStdVector(mveDevice, vertices);
		std::cout << "Creating MveGameObject..." << '\n';
		auto latticeGameObject = MveGameObject::createGameObject();
		std::cout << "Assigning model and transform..." << '\n';
		latticeGameObject.model = mveModel;
		latticeGameObject.transform.translation = { 0.f,0.f,0.f };
		latticeGameObject.transform.scale = glm::vec3{ 1.f, 1.f, 1.f };
		std::cout << "Emplacing gameobject..." << '\n';
		gameObjects.emplace(latticeGameObject.getId(), std::move(latticeGameObject));
		std::cout << "loadGameObjects finished!" << '\n';
	}
}