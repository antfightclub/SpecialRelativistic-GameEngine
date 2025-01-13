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
		VkRenderPass getUIRenderPass() const { return mveSwapChain->getUIRenderPass(); }
		float getAspectRatio() const { return mveSwapChain->extentAspectRatio(); }
		bool isFrameInProgress() const { return isFrameStarted; }
		VkFormat getSwapChainDepthFormat() const { return mveSwapChain->getDepthFormat(); }

		VkCommandBuffer getCurrentCommandBuffer() const {
			assert(isFrameStarted && "Cannot get command buffer when frame not in progress!");
			return commandBuffers[currentFrameIndex];
		}
		
		VkCommandBuffer getCurrentUICommandBuffer() const {
			assert(isFrameStarted && "Cannot get command buffer when frame not in progress!");
			return UICommandBuffers[currentFrameIndex];
		}

		int getFrameIndex() const {
			assert(isFrameStarted && "Cannot get frame index when frame not in progress!");
			return currentFrameIndex;
		}

		bool beginFrame();
		std::array<VkCommandBuffer, 2> getCurrentFrameCommandBuffers();
		void endFrame();
		void beginSwapChainRenderPass(VkCommandBuffer commandBuffer, VkRenderPass renderPass = VK_NULL_HANDLE);
		void endSwapChainRenderPass(VkCommandBuffer commandBuffer);
		void beginUIRenderPass(VkCommandBuffer commandBuffer);
		void endUIRenderPass(VkCommandBuffer commandBuffer);

	private:
		void createCommandBuffers();
		void createUICommandBuffers();
		void freeCommandBuffers();
		void freeUICommandBuffers();
		void recreateSwapChain();
		
		MveWindow& mveWindow;
		MveDevice& mveDevice;;
		std::unique_ptr<MveSwapChain> mveSwapChain;
		std::vector<VkCommandBuffer> commandBuffers;
		std::vector<VkCommandBuffer> UICommandBuffers;

		uint32_t currentImageIndex;
		int currentFrameIndex{ 0 };
		bool isFrameStarted{ false };
	};
}