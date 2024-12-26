#pragma once

#include "mve_descriptors.hpp"
#include "mve_window.hpp"
#include "mve_game_object.hpp"
#include "mve_device.hpp"
#include "mve_renderer.hpp"

//std
#include <memory>
#include <vector>

namespace mve {

	class RelativityApp {
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

		RelativityApp();
		~RelativityApp();

		RelativityApp(const RelativityApp&) = delete;
		RelativityApp& operator=(const RelativityApp&) = delete;

		void run();

	private:
		void loadGameObjects();

		MveWindow mveWindow{ WIDTH, HEIGHT, "Monativity.exe" };
		MveDevice mveDevice{ mveWindow };
		MveRenderer mveRenderer{ mveWindow, mveDevice };

		// note: order of declarations matters
		std::unique_ptr<MveDescriptorPool> globalPool{};
		MveGameObject::Map gameObjects;
	};
}