#include "imgui_render_system.hpp"

namespace mve {
	
	struct ImguiPushConstantData {
		glm::vec2 uScale{1.0};
		glm::vec2 uTranslate{ 0.0 };
	};
	

	ImguiRenderSystem::ImguiRenderSystem(MveDevice& device, VkRenderPass renderPass, VkDescriptorSetLayout descriptorSetLayout) : mveDevice{ device } {
		createPipelineLayout(descriptorSetLayout);
		createPipeline(renderPass);
	}

	ImguiRenderSystem::~ImguiRenderSystem() {
		vkDestroyPipelineLayout(mveDevice.device(), pipelineLayout, nullptr);
	}

	void ImguiRenderSystem::renderImgui(FrameInfo& frameInfo) {
		mvePipeline->bind(frameInfo.commandBuffer);

	}

	void ImguiRenderSystem::createPipelineLayout(VkDescriptorSetLayout globalDescriptorSetLayout) {
		
	}

	void ImguiRenderSystem::createPipeline(VkRenderPass renderPass) {

	}



}