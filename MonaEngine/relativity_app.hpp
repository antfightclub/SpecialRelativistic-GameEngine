#pragma once

// Engine related
#include "mve_descriptors.hpp"
#include "mve_window.hpp"
#include "mve_game_object.hpp"
#include "mve_device.hpp"
#include "mve_renderer.hpp"
#include "mve_frame_info.hpp"
#include "lattice.hpp"

//#include "relativity/unit_conversions.hpp"

// Spacetime Algebra
#include "spacetimealgebra/m4sta.hpp"
//#include "spacetimealgebra/mve_matrix_ops.hpp"

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

		void m4sta_testing_stuffs(Math::Vector4D X, Math::Vector4D lastX, double deltaTime);
		m4sta::mv commutatorProduct(m4sta::mv& a, m4sta::mv& b);
		m4sta::mv p3CrossProduct(m4sta::mv& A, m4sta::mv& B);
		void renderGUI(GuiInfo guiInfo);
		void GUITableFromMultivector(m4sta::mv& mv, const char* id);
		void GUITableFromMatrix(glm::mat4 mat, const char* id);

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