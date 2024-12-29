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
			.setMaxSets(MveSwapChain::MAX_FRAMES_IN_FLIGHT*2)
			.addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, MveSwapChain::MAX_FRAMES_IN_FLIGHT*2) // times 2 due to usage of Global Ubo + Lattice Ubo 
			.build();

		loadGameObjects();
	}

	RelativityApp::~RelativityApp() {}
	
	void RelativityApp::run() {

		std::cout << "start run!" << std::endl;


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

		// (I Think) this is buffers for each frame in flight
		std::vector<std::unique_ptr<MveBuffer>> globalUboBuffers(MveSwapChain::MAX_FRAMES_IN_FLIGHT);
		for (int i = 0; i < globalUboBuffers.size(); i++) {
			globalUboBuffers[i] = std::make_unique<MveBuffer>(
				mveDevice,
				sizeof(GlobalUbo),
				1,
				VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
				//&latticeUboBuffers[i]
			);
			globalUboBuffers[i]->map();
		}

		MveBuffer globalUboBuffer{
			mveDevice,
			sizeof(GlobalUbo),
			MveSwapChain::MAX_FRAMES_IN_FLIGHT,
			VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
			//&latticeUboBuffer,
			mveDevice.properties.limits.minUniformBufferOffsetAlignment,
		};
	
		
		globalUboBuffer.map();


		
		auto globalUboSetLayout = MveDescriptorSetLayout::Builder(mveDevice)
			.addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 1U) // Global Ubo 
			.addBinding(1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 1U)
			.build();
		
		/*auto latticeUboSetLayout = MveDescriptorSetLayout::Builder(mveDevice)
			.addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 1U)
			.build();
		*/
	
		std::vector<VkDescriptorSet> descriptorSets(MveSwapChain::MAX_FRAMES_IN_FLIGHT);
		for (int i = 0; i < descriptorSets.size(); i++) {	
			auto globalBufferInfo = globalUboBuffers[i]->descriptorInfo();
			auto latticeBufferInfo = latticeUboBuffers[i]->descriptorInfo();
			MveDescriptorWriter(*globalUboSetLayout, *globalPool)
				.writeBuffer(0, &globalBufferInfo)
				.writeBuffer(1, &latticeBufferInfo)
				.build(descriptorSets[i]);
			
			/*MveDescriptorWriter(*latticeUboSetLayout, *globalPool)
				.writeBuffer(0, &latticeBufferInfo)
				.build(descriptorSets[i]);*/
		}

		/*std::vector<VkDescriptorSet> latticeUboDescriptorSets(MveSwapChain::MAX_FRAMES_IN_FLIGHT);
		for (int i = 0; i < latticeUboDescriptorSets.size(); i++) {
			auto latticeBufferInfo = latticeUboBuffers[i]->descriptorInfo();
			MveDescriptorWriter(*latticeUboSetLayout, *globalPool)
				.writeBuffer(0, &latticeBufferInfo)
				.build(latticeUboDescriptorSets[i]);

		}*/

		std::cout << "globalDescriptorsets!!" << std::endl;

		LatticeWireframeSystem latticeRenderSystem{ mveDevice, mveRenderer.getSwapChainRenderPass(), globalUboSetLayout->getDescriptorSetLayout()};
		MveCamera camera{};
		camera.setViewDirection(glm::vec3(4.f, 0.f, 0.f), glm::vec3(0.5f, 0.f, 1.f));
		camera.setViewTarget(glm::vec3(4.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f));

		auto viewerObject = MveGameObject::createGameObject();
		viewerObject.transform.translation.z = 0.f;
		viewerObject.transform.translation.x = 4.f;
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

			camera.setPerspectiveProjection(glm::radians(100.f), aspect, 0.1f, 1000.0f);

		

			if (auto commandBuffer = mveRenderer.beginFrame()) {
				int frameIndex = mveRenderer.getFrameIndex();
				//std::vector<VkDescriptorSet> frameIndexedDescriptorSets = { globalUboDescriptorSets[frameIndex], latticeUboDescriptorSets[frameIndex] };
				FrameInfo frameInfo{
					frameIndex,
					frameTime,
					commandBuffer,
					camera,
					descriptorSets[frameIndex],
					gameObjects
				};

				// ***** update
				std::cout << "just before update in while loop!" << std::endl;
				// update global ubo buffer
				GlobalUbo globalUbo{};
				globalUbo.projection = camera.getProjection();
				globalUbo.view = camera.getView();
				globalUbo.inverseView = camera.getInverseView();
				globalUbo.ambientLightColor = { 1.f, 1.f, 1.f, .02f };
				globalUboBuffers[frameIndex]->writeToBuffer(&globalUbo);
				globalUboBuffers[frameIndex]->flush();
				/*globalUbo.Lorentz = glm::mat4{ 1.0f };
				globalUbo.Xp = camera.getPosition();
				globalUbo.Xo = glm::vec3{ 0.f, 0.f, 0.f };*/
				
				// TODO: update lattice ubo buffer with a lorentz matrix calculated in accordance with special relativit
				LatticeUbo latticeUbo{};
				latticeUbo.Xp = camera.getPosition();
				latticeUbo.Xo = glm::vec3{ 1.0f,0.0f,0.0f };
				latticeUbo.Lorentz = glm::mat4{ 0.f };
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
		Lattice lattice{50, 10, 5, 1, 1.0};
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
		latticeGameObject.transform.scale = glm::vec3{ 5.f, 5.f, 5.f };
		std::cout << "Emplacing gameobject..." << '\n';
		gameObjects.emplace(latticeGameObject.getId(), std::move(latticeGameObject));
		std::cout << "loadGameObjects finished!" << '\n';
	}
}