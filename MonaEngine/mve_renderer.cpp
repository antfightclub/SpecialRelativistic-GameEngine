#include "mve_renderer.hpp"

//std
#include <stdexcept>
#include <array>

namespace mve {

	MveRenderer::MveRenderer(MveWindow& window, MveDevice& device) : mveWindow{ window }, mveDevice{ device } {
		recreateSwapChain();
		createCommandBuffers();
		createUICommandBuffers();
	}

	MveRenderer::~MveRenderer() { freeCommandBuffers(); freeUICommandBuffers(); }

	
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

	void MveRenderer::createUICommandBuffers() {
		UICommandBuffers.resize(MveSwapChain::MAX_FRAMES_IN_FLIGHT);

		VkCommandBufferAllocateInfo allocInfo = {};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = mveDevice.getUICommandPool();
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = static_cast<uint32_t>(UICommandBuffers.size());

		if (vkAllocateCommandBuffers(mveDevice.device(), &allocInfo, UICommandBuffers.data()) != VK_SUCCESS) {
			throw std::runtime_error("Unable to allocate UI command buffers!");
		}
	}

	void MveRenderer::freeCommandBuffers() {
		vkFreeCommandBuffers(mveDevice.device(), mveDevice.getCommandPool(), static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());
		commandBuffers.clear();
	}

	void MveRenderer::freeUICommandBuffers() {
		vkFreeCommandBuffers(mveDevice.device(), mveDevice.getUICommandPool(), static_cast<uint32_t>(UICommandBuffers.size()), UICommandBuffers.data());
		UICommandBuffers.clear();
	}

	bool MveRenderer::beginFrame() {
		assert(!isFrameStarted && "Can't call beginFrame while already in progress!");

		auto result = mveSwapChain->acquireNextImage(&currentImageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR) {
			recreateSwapChain();
			return false;
		}

		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
			throw std::runtime_error("failed to acquire swap chain image!");
		}

		isFrameStarted = true;
		return true;

		
	}

	std::array<VkCommandBuffer, 2> MveRenderer::getCurrentFrameCommandBuffers() {
		assert(isFrameStarted && "Can't call getCurrentFrameCommandBuffers uf frame is not in progress!");
		auto commandBuffer = getCurrentCommandBuffer();
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
			throw std::runtime_error("failed to begin recording command buffer!");
		}

		auto uiCommandBuffer = getCurrentUICommandBuffer();
		VkCommandBufferBeginInfo cmdBufferBegin = {};
		cmdBufferBegin.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		cmdBufferBegin.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		if (vkBeginCommandBuffer(uiCommandBuffer, &cmdBufferBegin) != VK_SUCCESS) {
			throw std::runtime_error("Unable to start recording UI command buffer!");
		}
		std::array<VkCommandBuffer, 2> commandBuffers = { commandBuffer, uiCommandBuffer };
		return commandBuffers;
	}


	void MveRenderer::endFrame() {
		assert(isFrameStarted && "Can't call endFrame while frame is not in progress!");
		auto commandBuffer = getCurrentCommandBuffer();
		if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
			throw std::runtime_error("failed to record command buffer!");
		}

		auto uiCommandBuffer = getCurrentUICommandBuffer();
		if (vkEndCommandBuffer(uiCommandBuffer) != VK_SUCCESS) {
			throw std::runtime_error("failed to record UI command buffer!");
		}

		std::array<VkCommandBuffer, 2> cmdBuffers = { commandBuffer, uiCommandBuffer };

		auto result = mveSwapChain->submitCommandBuffers(&cmdBuffers, &currentImageIndex);

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

		std::array<VkClearValue, 2> clearValues{};
		clearValues[0].color = { 0.01f, 0.01f, 0.01f, 1.0f };
		clearValues[1].depthStencil = { 1.0f, 0 };
		//clearValues[2].color = { 0.01f, 0.01f, 0.01f, 1.0f };
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
		assert(isFrameStarted && "can't call endSwapchainRenderPass if frame is not in progress!");
		assert(commandBuffer == getCurrentCommandBuffer() && "can't end render pass on command buffer from a different frame!");

		vkCmdEndRenderPass(commandBuffer);
	}

	void MveRenderer::beginUIRenderPass(VkCommandBuffer commandBuffer) {
		assert(isFrameStarted && "can't call beginUIRenderPass if frame is not in progress!");
		assert(commandBuffer == getCurrentUICommandBuffer() && "can't begin render pass on command buffer from a different frame!");

		VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
		VkRenderPassBeginInfo renderPassBeginInfo = {};
		renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassBeginInfo.renderPass = mveSwapChain->getUIRenderPass();
		renderPassBeginInfo.framebuffer = mveSwapChain->getUIFrameBuffer(currentImageIndex);
		renderPassBeginInfo.renderArea.extent.width = mveSwapChain->getSwapChainExtent().width;
		renderPassBeginInfo.renderArea.extent.height = mveSwapChain->getSwapChainExtent().height;
		renderPassBeginInfo.clearValueCount = 1;
		renderPassBeginInfo.pClearValues = &clearColor;

		vkCmdBeginRenderPass(commandBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
	}

	void MveRenderer::endUIRenderPass(VkCommandBuffer commandBuffer) {
		assert(isFrameStarted && "can't call endUIRenderPass if frame is not in progress!");
		assert(commandBuffer == getCurrentUICommandBuffer() && "can't end UI render pass on command buffer from a different frame!");

		vkCmdEndRenderPass(commandBuffer);
	}

	//void MveRenderer::recordUICommands() {
	//	VkCommandBufferBeginInfo cmdBufferBegin = {};
	//	cmdBufferBegin.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	//	cmdBufferBegin.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	//	if (vkBeginCommandBuffer(getCurrentUICommandBuffer(), &cmdBufferBegin) != VK_SUCCESS) {
	//		throw std::runtime_error("Unable to start recording UI command buffer!");
	//	}

	//	VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
	//	VkRenderPassBeginInfo renderPassBeginInfo = {};
	//	renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	//	renderPassBeginInfo.renderPass = mveSwapChain->getUIRenderPass();
	//	renderPassBeginInfo.framebuffer = mveSwapChain->getUIFrameBuffer(currentImageIndex);
	//	renderPassBeginInfo.renderArea.extent.width = mveSwapChain->getSwapChainExtent().width;
	//	renderPassBeginInfo.renderArea.extent.height = mveSwapChain->getSwapChainExtent().height;
	//	renderPassBeginInfo.clearValueCount = 1;
	//	renderPassBeginInfo.pClearValues = &clearColor;

	//	vkCmdBeginRenderPass(UICommandBuffers[currentImageIndex], &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

	//	// IMGUI_IMPL_RENDERDRAWDATA ???

	//	vkCmdEndRenderPass(UICommandBuffers[currentImageIndex]);
	//	
	//	if (vkEndCommandBuffer(UICommandBuffers[currentImageIndex]) != VK_SUCCESS) {
	//		throw std::runtime_error("Failed to record UI command buffers!");
	//	}

	//}

} // namespace mve