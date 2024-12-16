#pragma once

#include "mve_window.hpp"
#include "mve_pipeline.hpp"
#include "mve_device.hpp"
#include "mve_swap_chain.hpp"
#include "mve_model.hpp"

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
		void loadModels();
		void createPipelineLayout();
		void createPipeline();
		void createCommandBuffers();
		void freeCommandBuffers();
		void drawFrame();
		void recreateSwapChain();
		void recordCommandBuffer(int imageIndex);

		MveWindow mveWindow{ WIDTH, HEIGHT, "Hello Mona!" };
		MveDevice mveDevice{ mveWindow };
		std::unique_ptr<MveSwapChain> mveSwapChain;
		std::unique_ptr<MvePipeline> mvePipeline;
		VkPipelineLayout pipelineLayout;
		std::vector<VkCommandBuffer> commandBuffers;
		std::unique_ptr<MveModel> mveModel;
	};
}