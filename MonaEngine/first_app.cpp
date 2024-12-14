#include "first_app.hpp"

namespace mve {
	void FirstApp::run() {
		while (!mveWindow.shouldClose()) {
			glfwPollEvents();

		}
	}
} // namespace mve