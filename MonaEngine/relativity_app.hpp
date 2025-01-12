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

// I think I need to take inspiration from LSBattle/model/polygon.py instead of 
// LSBattle/entity/wireframe.py! I can worry about a lattice later, but right now
// it's just most important that I get a single object working in relativity...
// I may also need to work it up a bit more from the ground up with more thoughts
// put into handling coordinate systems and such! 
// So I should probably take some time to analyze how game update logic works and 
// try to implement some game logic handling in a class like SpecialRelativityHandler 
// or smth like that, to keep track of gameobjects and their worldlines and such.

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
		
		void printGLMMat4(glm::mat4 temp) {
			// mat4[row][col]
			std::cout <<
			 "col0 "	<< temp[0][0] << ", " << temp[0][1] << ", " << temp[0][2] << ", " << temp[0][3] << "\n" <<
			 "col1 "	<< temp[1][0] << ", " << temp[1][1] << ", " << temp[1][2] << ", " << temp[1][3] << "\n" <<
			 "col2 "	<< temp[2][0] << ", " << temp[2][1] << ", " << temp[2][2] << ", " << temp[2][3] << "\n" <<
			 "col3 "	<< temp[3][0] << ", " << temp[3][1] << ", " << temp[3][2] << ", " << temp[3][3] << "\n"
				<< std::endl;
		}

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