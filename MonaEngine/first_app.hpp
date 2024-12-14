#pragma once

#include "mve_window.hpp"
#include "mve_pipeline.hpp"
#include "mve_device.hpp"
#include "mve_swap_chain.hpp"

//std
#include <memory>
#include <vector>

namespace mve {

	class FirstApp {

	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

		FirstApp();
		~FirstApp();

		FirstApp(const FirstApp&) = delete;
		FirstApp& operator=(const FirstApp&) = delete;

		void run();

	private:
		void createPipelineLayout();
		void createPipeline();
		void createCommandBuffers();
		void drawFrame();

		MveWindow mveWindow{ WIDTH, HEIGHT, "Hello Mona!" };
		MveDevice mveDevice{ mveWindow };
		MveSwapChain mveSwapChain{ mveDevice, mveWindow.getExtent() };
		std::unique_ptr<MvePipeline> mvePipeline;
		VkPipelineLayout pipelineLayout;
		std::vector<VkCommandBuffer> commandBuffers;
	};
}