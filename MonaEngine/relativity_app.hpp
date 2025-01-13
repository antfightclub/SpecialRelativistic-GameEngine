#pragma once

// Engine related
#include "mve_descriptors.hpp"
#include "mve_window.hpp"
#include "mve_game_object.hpp"
#include "mve_device.hpp"
#include "mve_renderer.hpp"

// Dear ImGui 
#include "external/imgui/imgui.h"
#include "external/imgui/imgui_impl_glfw.h"
#include "external/imgui/imgui_impl_vulkan.h"

//std
#include <memory>
#include <vector>
#include <iostream>

// TODO: Create another object and render it according to its own velocity
// I think this is probably the best path:
// - See how world.py performs Action, creating L and LL.
// - Go to Solar.py and see how its draw method works, it calculates something new
// - Go to Polygon.py and see how polygons are rendered (here will be the shaders)

namespace mve {
	// Application class
	class RelativityApp {
	public:
		static constexpr int WIDTH = 1280;
		static constexpr int HEIGHT = 720;

		RelativityApp();
		~RelativityApp();

		RelativityApp(const RelativityApp&) = delete;
		RelativityApp& operator=(const RelativityApp&) = delete;

		void run();
		
	private:

		int N = 50;
		int L = 5;

		void setupDearImgui();
		void loadGameObjects();
		

		MveWindow mveWindow{ WIDTH, HEIGHT, "Monativity.exe" };
		MveDevice mveDevice{ mveWindow };
		MveRenderer mveRenderer{ mveWindow, mveDevice };

		// note: order of declarations matters (?)	
		std::unique_ptr<MveDescriptorPool> globalPool{};
		std::unique_ptr<MveDescriptorPool> UIDescriptorPool{};
		MveGameObject::Map gameObjects;
	};
}