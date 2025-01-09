#include "mve_renderer.hpp"

//std
#include <stdexcept>
#include <array>

namespace mve {

	MveRenderer::MveRenderer(MveWindow& window, MveDevice& device) : mveWindow{ window }, mveDevice{ device } {
		recreateSwapChain();
		createCommandBuffers();
	}

	MveRenderer::~MveRenderer() { freeCommandBuffers(); }

	
	void MveRenderer::recreateSwapChain() {
		auto extent = mveWindow.getExtent();
		while (extent.width == 0 || extent.height == 0) {
			extent = mveWindow.getExtent();
			glfwWaitEvents();
		}

		vkDeviceWaitIdle(mveDevice.device());

		if (mveSwapChain == nullptr) {
			mveSwapChain = std::make_unique<MveSwapChain>(mveDevice, extent);
		}
		else {
			std::shared_ptr<MveSwapChain> oldSwapChain = std::move(mveSwapChain);
			mveSwapChain = std::make_unique<MveSwapChain>(mveDevice, extent, oldSwapChain);

			if (!oldSwapChain->compareSwapFormats(*mveSwapChain.get())) {
				throw std::runtime_error("Swap chain image or depth format has changed!");
			}
		}
				
		// wawa
	}

	void MveRenderer::createCommandBuffers() {

		commandBuffers.resize(MveSwapChain::MAX_FRAMES_IN_FLIGHT);

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = mveDevice.getCommandPool();
		allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

		if (vkAllocateCommandBuffers(mveDevice.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate command buffers!");
		}
	}

	void MveRenderer::freeCommandBuffers() {
		vkFreeCommandBuffers(mveDevice.device(), mveDevice.getCommandPool(), static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());
		commandBuffers.clear();
	}

	VkCommandBuffer MveRenderer::beginFrame() {
		assert(!isFrameStarted && "Can't call beginFrame while already in progress!");

		auto result = mveSwapChain->acquireNextImage(&currentImageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR) {
			recreateSwapChain();
			return nullptr;
		}

		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
			throw std::runtime_error("failed to acquire swap chain image!");
		}

		isFrameStarted = true;

		auto commandBuffer = getCurrentCommandBuffer();
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
			throw std::runtime_error("failed to begin recording command buffer!");
		}
		
		return commandBuffer;
	}

	void MveRenderer::endFrame() {
		assert(isFrameStarted && "Can't call endFrame while frame is not in progress!");
		auto commandBuffer = getCurrentCommandBuffer();
		if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
			throw std::runtime_error("failed to record command buffer!");
		}

		auto result = mveSwapChain->submitCommandBuffers(&commandBuffer, &currentImageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || mveWindow.wasWindowResized()) {
			mveWindow.resetWindowResizedFlag();
			recreateSwapChain();
		}else if (result != VK_SUCCESS) {
			throw std::runtime_error("failed to present swap chain image!");
		}

		isFrameStarted = false;
		currentFrameIndex = (currentFrameIndex + 1) % MveSwapChain::MAX_FRAMES_IN_FLIGHT;
	}

	void MveRenderer::beginSwapChainRenderPass(VkCommandBuffer commandBuffer, VkRenderPass otherRenderPass) {
		assert(isFrameStarted && "can't call beginSwapchainRenderPass if frame is not in progress!");
		assert(commandBuffer == getCurrentCommandBuffer() && "can't begin render pass on command buffer from a different frame!");

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;

		if (otherRenderPass == VK_NULL_HANDLE) {
			renderPassInfo.renderPass = mveSwapChain->getRenderPass();
		}
		else
		{
			renderPassInfo.renderPass = otherRenderPass;
		}

	
		renderPassInfo.framebuffer = mveSwapChain->getFrameBuffer(currentImageIndex);

		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = mveSwapChain->getSwapChainExtent();

		std::array<VkClearValue, 3> clearValues{};
		clearValues[0].color = { 0.01f, 0.01f, 0.01f, 1.0f };
		clearValues[1].depthStencil = { 1.0f, 0 };
		clearValues[2].color = { 0.01f, 0.01f, 0.01f, 1.0f };
		renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
		renderPassInfo.pClearValues = clearValues.data();

		vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = static_cast<float>(mveSwapChain->getSwapChainExtent().width);
		viewport.height = static_cast<float>(mveSwapChain->getSwapChainExtent().height);
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		VkRect2D scissor{ {0, 0}, mveSwapChain->getSwapChainExtent() };
		vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
		vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

	}

	void MveRenderer::endSwapChainRenderPass(VkCommandBuffer commandBuffer) {
		assert(isFrameStarted && "can't call endbeginSwapchainRenderPass if frame is not in progress!");
		assert(commandBuffer == getCurrentCommandBuffer() && "can't end render pass on command buffer from a different frame!");

		vkCmdEndRenderPass(commandBuffer);
	}

} // namespace mve