#pragma once

#include "mve_window.hpp"
#include "mve_device.hpp"
#include "mve_swap_chain.hpp"


//std
#include <cassert>
#include <memory>
#include <vector>

namespace mve {

	class MveRenderer {

	public:
		
		MveRenderer(MveWindow &window, MveDevice &device);
		~MveRenderer();

		MveRenderer(const MveRenderer&) = delete;
		MveRenderer& operator=(const MveRenderer&) = delete;
	
		VkRenderPass getSwapChainRenderPass() const { return mveSwapChain->getRenderPass(); }
		float getAspectRatio() const { return mveSwapChain->extentAspectRatio(); }
		bool isFrameInProgress() const { return isFrameStarted; }

		VkCommandBuffer getCurrentCommandBuffer() const {
			assert(isFrameStarted && "Cannot get command buffer when frame not in progress!");
			return commandBuffers[currentFrameIndex];
		}

		int getFrameIndex() const {
			assert(isFrameStarted && "Cannot get frame index when frame not in progress!");
			return currentFrameIndex;
		}

		VkCommandBuffer beginFrame();
		void endFrame();
		void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);
		void endSwapChainRenderPass(VkCommandBuffer commandBuffer);


	private:
		void createCommandBuffers();
		void freeCommandBuffers();
		void recreateSwapChain();
		
		MveWindow& mveWindow;
		MveDevice& mveDevice;;
		std::unique_ptr<MveSwapChain> mveSwapChain;
		std::vector<VkCommandBuffer> commandBuffers;

		uint32_t currentImageIndex;
		int currentFrameIndex{ 0 };
		bool isFrameStarted{ false };
	};
}