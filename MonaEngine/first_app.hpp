#pragma once

#include "mve_window.hpp"
#include "mve_pipeline.hpp"
#include "mve_device.hpp"

namespace mve {

	class FirstApp {

	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

		void run();

	private:
		MveWindow mveWindow{ WIDTH, HEIGHT, "Hello Mona!" };
		MveDevice mveDevice{ mveWindow };
		MvePipeline mvePipeline{mveDevice, "shaders/simple_shader.vert.spv", "shaders/simple_shader.frag.spv", MvePipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};

	};
}