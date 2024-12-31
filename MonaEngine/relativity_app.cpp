#include "relativity_app.hpp"

#include "keyboard_movement_controller.hpp"
#include "mve_camera.hpp"
#include "systems/lattice_wireframe_system.hpp"
#include "mve_buffer.hpp"
#include "lattice.hpp"

#include "relativity/math/Matrix44.hpp"
#include "relativity/math/Vector3.hpp"

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
		
		std::vector<VkDescriptorSet> descriptorSets(MveSwapChain::MAX_FRAMES_IN_FLIGHT);
		for (int i = 0; i < descriptorSets.size(); i++) {	
			auto globalBufferInfo = globalUboBuffers[i]->descriptorInfo();
			auto latticeBufferInfo = latticeUboBuffers[i]->descriptorInfo();
			MveDescriptorWriter(*globalUboSetLayout, *globalPool)
				.writeBuffer(0, &globalBufferInfo)
				.writeBuffer(1, &latticeBufferInfo)
				.build(descriptorSets[i]);
		}

		LatticeWireframeSystem latticeRenderSystem{ mveDevice, mveRenderer.getSwapChainRenderPass(), globalUboSetLayout->getDescriptorSetLayout()};
		MveCamera camera{};
		camera.setViewDirection(glm::vec3(0.f, 0.f, 0.f), glm::vec3(-0.5f, 0.f, 1.f));
		camera.setViewTarget(glm::vec3(4.f, 0.f, 0.f), glm::vec3(0.f, 0.f, 0.f));

		auto viewerObject = MveGameObject::createGameObject();
		//viewerObject.transform.translation.z = 4.f;
		KeyboardMovementController cameraController{};


		auto currentTime = std::chrono::high_resolution_clock::now();
		float timeSince = 0.f; // used to count time between frames!

		while (!mveWindow.shouldClose()) {
			glfwPollEvents();

			auto newTime = std::chrono::high_resolution_clock::now();
			float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
			float dt = frameTime - timeSince;
			
			std::cout << "frameTime = " << frameTime << " and dt = "  << dt << std::endl;

			glm::vec3 movedir = cameraController.moveInPlaneXZ(mveWindow.getGLFWwindow(), frameTime, viewerObject);
			camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

			float aspect = mveRenderer.getAspectRatio();

			camera.setPerspectiveProjection(glm::radians(100.f), aspect, 0.1f, 10000.0f);

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

				// ***** update
				
				// update global ubo buffer
				GlobalUbo globalUbo{};
				globalUbo.projection = camera.getProjection();
				globalUbo.view = camera.getView();
				globalUbo.inverseView = camera.getInverseView();
				globalUbo.ambientLightColor = { 1.f, 1.f, 1.f, .02f };
				globalUboBuffers[frameIndex]->writeToBuffer(&globalUbo);
				globalUboBuffers[frameIndex]->flush();

				glm::vec3 Xp = camera.getPosition();
				int xo = int((Xp.y / (50 / 10)) * (50 / 10));
				int yo = int((Xp.z / (50 / 10)) * (50 / 10));
				int zo = int((Xp.x / (50 / 10)) * (50 / 10));
				Math::Matrix44 U{};

				if (movedir.length() > 0.0) {
					U = Math::Matrix44::Lorentz(Math::Vector4D{ 1.0, movedir.x, movedir.y , movedir.z });
				}
				else {
					U = Math::Matrix44::Lorentz(Math::Vector4D{ 1.0, 0.0, 0.0, 0.0 });
				}
				
				//Math::Vector4D u = Math::Vector4D{};

				//U = Math::Matrix44::Lorentz(u);
				std::cout << "********** START OF PRINTING MATRICES **********" << std::endl;

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



				

				// TODO: update lattice ubo buffer with a lorentz matrix calculated in accordance with special relativity
				LatticeUbo latticeUbo{};
				latticeUbo.Xp = Xp;
				latticeUbo.Xo = glm::vec3{ -xo, yo, -zo };
				latticeUbo.Lorentz = U.toGLM();
				latticeUboBuffers[frameIndex]->writeToBuffer(&latticeUbo);
				latticeUboBuffers[frameIndex]->flush();
				latticeUboBuffer.flushIndex(frameIndex);

				// Render
				mveRenderer.beginSwapChainRenderPass(commandBuffer);
				
				// order matters (if semitransparency is involved)
				latticeRenderSystem.renderWireframe(frameInfo);

				mveRenderer.endSwapChainRenderPass(commandBuffer);
				mveRenderer.endFrame();				
			}
			timeSince = frameTime;
		}

		vkDeviceWaitIdle(mveDevice.device());
	}

	void RelativityApp::loadGameObjects() {
		// generate lattice
		Lattice lattice{50, 10, 5, 1, 5.0};

		auto vertices = lattice.getVertices();
		//auto indices = lattice.getIndices();

		std::cout << "printing out ALL lattice vertices!" << std::endl;
		
		// This takes a long time!
		//for (auto& vert : vertices) {
		//	std::cout << "{ " << vert.x << ", " << vert.y << ", " << vert.z << " }\n";
		//}

		std::shared_ptr<MveModel> mveModel = MveModel::createModelFromStdVector(mveDevice, vertices);

		auto latticeGameObject = MveGameObject::createGameObject();

		latticeGameObject.model = mveModel;
		latticeGameObject.transform.translation = { 0.f, 0.f, 0.f };
		latticeGameObject.transform.scale = glm::vec3{ 1.f, 1.f, 1.f };
		gameObjects.emplace(latticeGameObject.getId(), std::move(latticeGameObject));
	}
}