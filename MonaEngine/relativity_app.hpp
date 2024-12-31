#pragma once

#include "mve_descriptors.hpp"
#include "mve_window.hpp"
#include "mve_game_object.hpp"
#include "mve_device.hpp"
#include "mve_renderer.hpp"

//std
#include <memory>
#include <vector>
#include <iostream>

// Perhaps I need to pass an array of descriptor set handles!

namespace mve {

	class RelativityApp {
	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

		RelativityApp();
		~RelativityApp();

		RelativityApp(const RelativityApp&) = delete;
		RelativityApp& operator=(const RelativityApp&) = delete;

		void run();
		
		void printGLMMat4(glm::mat4 temp) {
			// mat4[row][col]
			std::cout <<
				temp[0][0] << ", " << temp[0][1] << ", " << temp[0][2] << ", " << temp[0][3] << "\n" <<
				temp[1][0] << ", " << temp[1][1] << ", " << temp[1][2] << ", " << temp[1][3] << "\n" <<
				temp[2][0] << ", " << temp[2][1] << ", " << temp[2][2] << ", " << temp[2][3] << "\n" <<
				temp[3][0] << ", " << temp[3][1] << ", " << temp[3][2] << ", " << temp[3][3] << "\n"
				<< std::endl;
		}

	private:

		int N = 10;
		int L = 5;

		void loadGameObjects();

		MveWindow mveWindow{ WIDTH, HEIGHT, "Monativity.exe" };
		MveDevice mveDevice{ mveWindow };
		MveRenderer mveRenderer{ mveWindow, mveDevice };

		// note: order of declarations matters
		std::unique_ptr<MveDescriptorPool> globalPool{};
		MveGameObject::Map gameObjects;
	};
}