#pragma once

#include "mve_window.hpp"


namespace mve {

	class FirstApp {

	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

		void run();

	private:
		MveWindow mveWindow{ WIDTH, HEIGHT, "Hello Mona!" };

	};
}