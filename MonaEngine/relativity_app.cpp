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


		vkDeviceWaitIdle(mveDevice.device());
	}

	void RelativityApp::loadGameObjects() {
		// generate lattice
		Lattice lattice;
		lattice.makeLattice(30.0, 100.0, 1.0);
		auto vertices = lattice.getVertices();
		auto indices = lattice.getIndices();
		std::shared_ptr<MveModel> mveModel = MveModel::createModelFromStdVectors(mveDevice, vertices, indices);
		auto latticeGameObject = MveGameObject::createGameObject();
		latticeGameObject.model = mveModel;
		latticeGameObject.transform.translation = { 0.f,0.f,0.f };
		latticeGameObject.transform.scale = glm::vec3{ 1.f, 1.f, 1.f };
		gameObjects.emplace(latticeGameObject.getId(), std::move(latticeGameObject));
	}
}