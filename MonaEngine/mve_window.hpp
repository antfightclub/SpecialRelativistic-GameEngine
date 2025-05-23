#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "keyboard_input_controller.hpp"

#include <string>

namespace mve {

	struct KeyState {
		int k_accel = 0;
		int k_accel_priority = 0;
		bool k_turn_right = false;
		bool k_turn_left = false;
		bool k_turn_up = false;
		bool k_turn_down = false;
		int k_turn_priority_1 = 0;
		int k_turn_priority_2 = 0;
		bool k_brake = false;
	};


	class MveWindow {

	public:
		MveWindow(int w, int h, std::string name);
		~MveWindow();

		MveWindow(const MveWindow&) = delete;
		MveWindow& operator=(const MveWindow&) = delete;

		bool shouldClose() { return glfwWindowShouldClose(window); }
		VkExtent2D getExtent() { return { static_cast<uint32_t>(width), static_cast<uint32_t>(height) }; }
		bool wasWindowResized() { return framebufferResized; }
		void resetWindowResizedFlag() { framebufferResized = false; }
		GLFWwindow* getGLFWwindow() const { return window; }
		void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);
		

		void onKey(int key, int scancode, int action, int mods);
		void updateKeyMap(int key, int action);

		KeyState k_state{};

	private:
		static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
		void initWindow();

		int width;
		int height;
		bool framebufferResized = false;

		KeyboardInputController keyboardController{};

		
		std::string windowName;
		GLFWwindow* window;
	};
}