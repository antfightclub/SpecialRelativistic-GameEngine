#include "first_app.hpp"

#include "keyboard_movement_controller.hpp"
#include "mve_camera.hpp"
#include "simple_render_system.hpp"

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
		loadGameObjects();
	}

	FirstApp::~FirstApp() {}

	void FirstApp::run() {
		SimpleRenderSystem simpleRenderSystem{ mveDevice, mveRenderer.getSwapChainRenderPass() };
        MveCamera camera{};
        camera.setViewDirection(glm::vec3(0.f), glm::vec3(0.5f, 0.f, 1.f));
        camera.setViewTarget(glm::vec3(-1.f, -2.f, -2.f), glm::vec3(0.f, 0.f, 2.5f));

        auto viewerObject = MveGameObject::createGameObject();
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
            camera.setPerspectiveProjection(glm::radians(50.f), aspect, 0.1f, 10.f);

			if (auto commandBuffer = mveRenderer.beginFrame()) {

				mveRenderer.beginSwapChainRenderPass(commandBuffer);
				simpleRenderSystem.renderGameObjects(commandBuffer, gameObjects, camera);
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
		flatVase.transform.translation = { -.5f, .5f, 1.5f };
		flatVase.transform.scale = glm::vec3{ 3.f, 1.5f, 3.f };
		gameObjects.push_back(std::move(flatVase));

		mveModel = MveModel::createModelFromFile(mveDevice, "models/smooth_vase.obj");
		auto smoothVase = MveGameObject::createGameObject();
		smoothVase.model = mveModel;
		smoothVase.transform.translation = { .5f, .5f, 1.5f };
		smoothVase.transform.scale = glm::vec3{ 3.f, 1.5f, 3.f };
		gameObjects.push_back(std::move(smoothVase));
	}

} // namespace mve