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

	class FirstApp {

	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

		FirstApp();
		~FirstApp();

		FirstApp(const FirstApp&) = delete;
		FirstApp& operator=(const FirstApp&) = delete;

		void run();

	private:
		void loadGameObjects();
	
		MveWindow mveWindow{ WIDTH, HEIGHT, "MonaCube.exe" };
		MveDevice mveDevice{ mveWindow };
		MveRenderer mveRenderer{ mveWindow, mveDevice };

		// note: order of declarations matters
		std::unique_ptr<MveDescriptorPool> globalPool{};
		MveGameObject::Map gameObjects;
	};
}