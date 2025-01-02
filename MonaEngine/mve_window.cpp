#include "mve_window.hpp"

//std
#include <stdexcept>
namespace mve {
	MveWindow::MveWindow(int w, int h, std::string name) : width(w), height(h), windowName(name) {
		initWindow();
	}

	MveWindow::~MveWindow() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void MveWindow::initWindow() {
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(window, this);
		glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
		auto keyCallbackFunc = [](GLFWwindow* w, int key, int scancode, int action, int mods) {
			static_cast<MveWindow*>(glfwGetWindowUserPointer(w))->onKey(key, scancode, action, mods);
			};
		glfwSetKeyCallback(window, keyCallbackFunc);
	
	}

	void MveWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface) {
		if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
			throw std::runtime_error("failed to create window surface!");
		}
	}

	void MveWindow::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
		auto mveWindow = reinterpret_cast<MveWindow*>(glfwGetWindowUserPointer(window));
		mveWindow->framebufferResized = true;
		mveWindow->width = width;
		mveWindow->height = height;

	}

	void MveWindow::onKey(int key, int scancode, int action, int mods) {
		
		updateKeyMap(key, action);
		
	}

	void MveWindow::updateKeyMap(int key, int action) {
		// Evil keymap

		// Key Down
		if (key == keyboardController.keys.accel_forward && action == GLFW_PRESS) {
			k_state.k_accel |= 1;
		}
		else if (key == keyboardController.keys.accel_back && action == GLFW_PRESS) {
			k_state.k_accel |= 2;
		}
		else if (key == keyboardController.keys.accel_right && action == GLFW_PRESS) {
			k_state.k_accel |= 4;
			k_state.k_accel_priority = 0;
		}
		else if (key == keyboardController.keys.accel_left && action == GLFW_PRESS) {
			k_state.k_accel |= 8;
			k_state.k_accel_priority = 1;
		}
		else if (key == keyboardController.keys.turn_right && action == GLFW_PRESS) {
			k_state.k_turn_right = true;
			k_state.k_turn_priority_1 = 0;
		}
		else if (key == keyboardController.keys.turn_left && action == GLFW_PRESS) {
			k_state.k_turn_left = true;
			k_state.k_turn_priority_1 = 1;
		}
		else if (key == keyboardController.keys.turn_up && action == GLFW_PRESS) {
			k_state.k_turn_up = true;
			k_state.k_turn_priority_2 = 0;
		}
		else if (key == keyboardController.keys.turn_down && action == GLFW_PRESS) {
			k_state.k_turn_down = true;
			k_state.k_turn_priority_2 = 1;
		}

		// Key Release
		if (key == keyboardController.keys.accel_forward && action == GLFW_RELEASE) {
			if ((k_state.k_accel & 1) == 1) {
				k_state.k_accel -= 1;
			}
		}
		else if (key == keyboardController.keys.accel_back && action == GLFW_RELEASE) {
			if ((k_state.k_accel & 2) == 2) {
				k_state.k_accel -= 2;
			}
		}
		else if (key == keyboardController.keys.accel_back && action == GLFW_RELEASE) {
			if ((k_state.k_accel & 2) == 2) {
				k_state.k_accel -= 2;
			}
		}
		else if (key == keyboardController.keys.accel_right && action == GLFW_RELEASE) {
			if ((k_state.k_accel & 4) == 4) {
				k_state.k_accel -= 4;
			}
		}
		else if (key == keyboardController.keys.accel_left && action == GLFW_RELEASE) {
			if ((k_state.k_accel & 8) == 8) {
				k_state.k_accel -= 8;
			}
		}
		else if (key == keyboardController.keys.turn_right && action == GLFW_RELEASE) {
			k_state.k_turn_right = false;
		}
		else if (key == keyboardController.keys.turn_left && action == GLFW_RELEASE) {
			k_state.k_turn_left = false;
		}
		else if (key == keyboardController.keys.turn_up && action == GLFW_RELEASE) {
			k_state.k_turn_up = false;
		}
		else if (key == keyboardController.keys.turn_down && action == GLFW_RELEASE) {
			k_state.k_turn_down = false;
		}
	}


}