#pragma once

#include "mve_window.hpp"
#include "mve_pipeline.hpp"
#include "mve_device.hpp"
#include "mve_swap_chain.hpp"

namespace mve {

	class FirstApp {

	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

		void run();

	private:
		MveWindow mveWindow{ WIDTH, HEIGHT, "Hello Mona!" };
		MveDevice mveDevice{ mveWindow };
		MveSwapChain mveSwapChain{ mveDevice, mveWindow.getExtent() };
		MvePipeline mvePipeline{mveDevice, "shaders/simple_shader.vert.spv", "shaders/simple_shader.frag.spv", MvePipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};

	};
}