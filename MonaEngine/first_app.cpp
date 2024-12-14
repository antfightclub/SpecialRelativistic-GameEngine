#include "first_app.hpp"

//std
#include <stdexcept>


namespace mve {

	FirstApp::FirstApp() {
		createPipelineLayout();
		createPipeline();
		createCommandBuffers();
	}

	FirstApp::~FirstApp() { vkDestroyPipelineLayout(mveDevice.device(), pipelineLayout, nullptr); }

	void FirstApp::run() {
		while (!mveWindow.shouldClose()) {
			glfwPollEvents();

		}
	}

	void FirstApp::createPipelineLayout() {
		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pSetLayouts = nullptr;
		pipelineLayoutInfo.pushConstantRangeCount = 0;
		pipelineLayoutInfo.pPushConstantRanges = nullptr;
		if (vkCreatePipelineLayout(mveDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
			throw std::runtime_error("failed to create pipeline layout!");
		}
	}

	void FirstApp::createPipeline() {
		auto pipelineConfig = MvePipeline::defaultPipelineConfigInfo(mveSwapChain.width(), mveSwapChain.height());
		pipelineConfig.renderPass = mveSwapChain.getRenderPass();
		pipelineConfig.pipelineLayout = pipelineLayout;
		mvePipeline = std::make_unique<MvePipeline>(
			mveDevice,
			"shaders/simple_shader.vert.spv",
			"shaders/simple_shader.frag.spv",
			pipelineConfig);
	};

	void FirstApp::createCommandBuffers() {}
	void FirstApp::drawFrame() {}

} // namespace mve