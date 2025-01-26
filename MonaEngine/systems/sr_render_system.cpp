#include "sr_render_system.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm.hpp>
#include <gtc/constants.hpp>

#include <stdexcept>
#include <array>
#include <iostream>

namespace mve {
	struct PushConstantData {
		glm::mat4 modelMatrix{ 1.f };
	};

	SRRenderSystem::SRRenderSystem(MveDevice& device, VkRenderPass renderPass, VkDescriptorSetLayout descriptorSetLayout) : mveDevice{ device } {
		createPipelineLayout(descriptorSetLayout);
		createPipeline(renderPass);
	}

	SRRenderSystem::~SRRenderSystem() { vkDestroyPipelineLayout(mveDevice.device(), pipelineLayout, nullptr); }

	void SRRenderSystem::createPipelineLayout(VkDescriptorSetLayout globalDescriptorSetLayout) {
		VkPushConstantRange pushConstantRange{};
		pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
		pushConstantRange.offset = 0;
		pushConstantRange.size = sizeof(PushConstantData);
		
		std::vector<VkDescriptorSetLayout> descriptorSetLayouts{ globalDescriptorSetLayout };

		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size());
		pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();
		pipelineLayoutInfo.pushConstantRangeCount = 1;
		pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;
		if (vkCreatePipelineLayout(mveDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
			throw std::runtime_error("failed to create pipeline layout!");
		}
	}

	void SRRenderSystem::createPipeline(VkRenderPass renderPass) {
		assert(pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout!");

		PipelineConfigInfo pipelineConfig{};

		MvePipeline::defaultPipelineConfigInfo(pipelineConfig);
		MvePipeline::enableAlphaBlending(pipelineConfig);
		pipelineConfig.renderPass = renderPass;
		pipelineConfig.pipelineLayout = pipelineLayout;
		mvePipeline = std::make_unique<MvePipeline>(
			mveDevice,
			"./shaders/polygon_shader.vert.spv",
			"./shaders/polygon_shader.frag.spv",
			pipelineConfig);
		mvePipeline->enableAlphaBlending(pipelineConfig);
	}

	void SRRenderSystem::render(FrameInfo& frameInfo, unsigned int NOTid) {
		mvePipeline->bind(frameInfo.frameCommandBuffers.mainCommandBuffer);
		vkCmdBindDescriptorSets(
			frameInfo.frameCommandBuffers.mainCommandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			pipelineLayout,
			0,
			1,
			&frameInfo.descriptorSet,
			0,
			nullptr
		);

		// should somehow be able to *not* render the lattice using this system
		// need a way to discern between game objects... Perhaps by passing a
		// list of MveGameObject ID's to exclude.
		for (auto& kv : frameInfo.gameObjects) {
			if (kv.first == NOTid) continue;
			auto& obj = kv.second;
			if (obj.model == nullptr) continue; // Skip gameobject if it has no model (e.g. camera)
			PushConstantData push{};
			auto modelMatrix = obj.transform.mat4();
			push.modelMatrix = modelMatrix;

			vkCmdPushConstants(
				frameInfo.frameCommandBuffers.mainCommandBuffer,
				pipelineLayout,
				VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
				0,
				sizeof(PushConstantData),
				&push);
			obj.model->bind(frameInfo.frameCommandBuffers.mainCommandBuffer);
			obj.model->draw(frameInfo.frameCommandBuffers.mainCommandBuffer);

		}
	}
}