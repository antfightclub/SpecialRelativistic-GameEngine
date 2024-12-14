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
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
	}

	void MveWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface) {
		if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
			throw std::runtime_error("failed to create window surface!");
		}
	}

}