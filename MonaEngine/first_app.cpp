#include "first_app.hpp"

#include "keyboard_movement_controller.hpp"
#include "mve_camera.hpp"
#include "systems/simple_render_system.hpp"
#include "systems/point_light_system.hpp"
#include "mve_buffer.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm.hpp>
#include <gtc/constants.hpp>

//std
#include <cassert>
#include <chrono>
#include <stdexcept>
#include <array>

namespace mve {

	FirstApp::FirstApp() {
		globalPool = MveDescriptorPool::Builder(mveDevice)
			.setMaxSets(MveSwapChain::MAX_FRAMES_IN_FLIGHT)
			.addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, MveSwapChain::MAX_FRAMES_IN_FLIGHT)
			.build();

		loadGameObjects();
	}

	FirstApp::~FirstApp() {}

	void FirstApp::run() {

		std::vector<std::unique_ptr<MveBuffer>> uboBuffers(MveSwapChain::MAX_FRAMES_IN_FLIGHT);
		for (int i = 0; i < uboBuffers.size(); i++) {
			uboBuffers[i] = std::make_unique<MveBuffer>(
				mveDevice,
				sizeof(GlobalUbo),
				1,
				VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, 
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
			);
			uboBuffers[i]->map();
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
			.addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT)
			.build();

		std::vector<VkDescriptorSet> globalDescriptorSets(MveSwapChain::MAX_FRAMES_IN_FLIGHT);
		for (int i = 0; i < globalDescriptorSets.size(); i++) {
			auto bufferInfo = uboBuffers[i]->descriptorInfo();
			MveDescriptorWriter(*globalSetLayout, *globalPool)
				.writeBuffer(0, &bufferInfo)
				.build(globalDescriptorSets[i]);
		}

		SimpleRenderSystem simpleRenderSystem{ mveDevice, mveRenderer.getSwapChainRenderPass(), globalSetLayout->getDescriptorSetLayout()};
		//PointLightSystem pointLightSystem{ mveDevice, mveRenderer.getSwapChainRenderPass(), globalSetLayout->getDescriptorSetLayout() };
        MveCamera camera{};
        camera.setViewDirection(glm::vec3(0.f), glm::vec3(0.5f, 0.f, 1.f));
        camera.setViewTarget(glm::vec3(-1.f, -2.f, -2.f), glm::vec3(0.f, 0.f, 2.5f));

        auto viewerObject = MveGameObject::createGameObject();
		viewerObject.transform.translation.z = -2.5f;
        KeyboardMovementController cameraController{};

        auto currentTime = std::chrono::high_resolution_clock::now();

		while (!mveWindow.shouldClose()) {
			glfwPollEvents();

            auto newTime = std::chrono::high_resolution_clock::now();
            float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
            currentTime = newTime;

            cameraController.moveInPlaneXZ(mveWindow.getGLFWwindow(), frameTime, viewerObject);
            camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

            float aspect = mveRenderer.getAspectRatio();
            camera.setPerspectiveProjection(glm::radians(50.f), aspect, 0.1f, 100.f);

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

			
				// update
				GlobalUbo ubo{};
				ubo.projection = camera.getProjection();
				ubo.view = camera.getView();
				ubo.inverseView = camera.getInverseView();
				//pointLightSystem.update(frameInfo, ubo);
				uboBuffers[frameIndex]->writeToBuffer(&ubo);
				uboBuffers[frameIndex]->flush();
				globalUboBuffer.flushIndex(frameIndex);

				// render
				mveRenderer.beginSwapChainRenderPass(commandBuffer);

				// order here matters (all solid objects first - then semitransparent objects after!)
				simpleRenderSystem.renderGameObjects(frameInfo);
				//pointLightSystem.render(frameInfo);
				
				mveRenderer.endSwapChainRenderPass(commandBuffer);
				mveRenderer.endFrame();
			}
		}

		vkDeviceWaitIdle(mveDevice.device());
	}



	void FirstApp::loadGameObjects() {
		std::shared_ptr<MveModel> mveModel = MveModel::createModelFromFile(mveDevice, "models/flat_vase.obj");
		auto flatVase = MveGameObject::createGameObject();
		flatVase.model = mveModel;
		flatVase.transform.translation = { -.5f, .5f, 0.f };
		flatVase.transform.scale = glm::vec3{ 3.f, 1.5f, 3.f };
		gameObjects.emplace(flatVase.getId(), std::move(flatVase));

		mveModel = MveModel::createModelFromFile(mveDevice, "models/smooth_vase.obj");
		auto smoothVase = MveGameObject::createGameObject();
		smoothVase.model = mveModel;
		smoothVase.transform.translation = { .5f, .5f, 0.f };
		smoothVase.transform.scale = glm::vec3{ 3.f, 1.5f, 3.f };
		gameObjects.emplace(smoothVase.getId(), std::move(smoothVase));

		mveModel = MveModel::createModelFromFile(mveDevice, "models/quad.obj");
		auto floor = MveGameObject::createGameObject();
		floor.model = mveModel;
		floor.transform.translation = { 0.f, .5f, 0.f };
		floor.transform.scale = glm::vec3{ 3.f, 1.f, 3.f };
		gameObjects.emplace(floor.getId(), std::move(floor));

		
		
		std::vector<glm::vec3> lightColors{
			{1.f, .1f, .1f},
			{.1f, .1f, 1.f},
			{.1f, 1.f, .1f},
			{1.f, 1.f, .1f},
			{.1f, 1.f, 1.f},
			{1.f, 1.f, 1.f}  //
		};

		for (int i = 0; i < lightColors.size(); i++) {
			auto pointLight = MveGameObject::makePointLight(0.2f);
			pointLight.color = lightColors[i];
			auto rotateLight = glm::rotate(glm::mat4(1.f), (i * glm::two_pi<float>()) / lightColors.size(), {0.f, -1.f, 0.f});
			pointLight.transform.translation = glm::vec3(rotateLight * glm::vec4(-1.f, -1.f, -1.f, 1.f));
			gameObjects.emplace(pointLight.getId(), std::move(pointLight));

		}

	}

} // namespace mve