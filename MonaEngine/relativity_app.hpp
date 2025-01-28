#pragma once

// Engine related
#include "mve_descriptors.hpp"
#include "mve_window.hpp"
#include "mve_game_object.hpp"
#include "mve_device.hpp"
#include "mve_renderer.hpp"

#include "lattice.hpp"

// Spacetime Algebra
#include "spacetimealgebra/m4sta.h"

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
		glm::mat4 m4sta_to_glm_Lorentz(m4sta::mv PlayerU);
		glm::mat4 m4sta_g23_J1_glm(double g23);
		glm::mat4 m4sta_neg_g13_J2_glm(double neg_g13);
		glm::mat4 m4sta_g12_J3_glm(double g12);
		glm::mat4 m4sta_g01_K1_glm(double g01);
		glm::mat4 m4sta_g02_K2_glm(double g02);
		glm::mat4 m4sta_g03_K3_glm(double g03);

		void m4sta_testing_stuffs();


		void setupDearImgui();
		void loadGameObjects();
		
		Lattice lattice{ 50, 5, 20, 1, 1.0 };
		unsigned int latticeGameObjectID = -1;

		MveWindow mveWindow{ WIDTH, HEIGHT, "Monativity.exe" };
		MveDevice mveDevice{ mveWindow };
		MveRenderer mveRenderer{ mveWindow, mveDevice };

		// note: order of declarations matters (?)	
		std::unique_ptr<MveDescriptorPool> globalPool{};
		std::unique_ptr<MveDescriptorPool> UIDescriptorPool{};
		MveGameObject::Map gameObjects;
	};
}