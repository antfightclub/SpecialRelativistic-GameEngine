#include "lattice_wireframe_system.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm.hpp>
#include <gtc/constants.hpp>

//std
#include <stdexcept>
#include <array>

namespace mve {
	
	struct SimplePushConstantData {
		glm::mat4 modelMatrix{ 1.f };
	};

	LatticeWireframeSystem::LatticeWireframeSystem(MveDevice& device, VkRenderPass renderPass, VkDescriptorSetLayout globalUboDescriptorSetLayout) : mveDevice{ device } {
		createPipelineLayout(globalUboDescriptorSetLayout);
		createPipeline(renderPass);
		//createpipeline pass renderpass
	}

	LatticeWireframeSystem::~LatticeWireframeSystem() { vkDestroyPipelineLayout(mveDevice.device(), pipelineLayout, nullptr); }

	void LatticeWireframeSystem::createPipelineLayout(VkDescriptorSetLayout globalDescriptorSetLayout) {

		VkPushConstantRange pushConstantRange{};
		pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
		pushConstantRange.offset = 0;
		pushConstantRange.size = sizeof(SimplePushConstantData);

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

	void LatticeWireframeSystem::createPipeline(VkRenderPass renderPass) {
		assert(pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout!");
		
		PipelineConfigInfo pipelineConfig{ };
		MvePipeline::wireframePipelineConfigInfo(pipelineConfig);
		pipelineConfig.renderPass = renderPass;
		pipelineConfig.pipelineLayout = pipelineLayout;
		mvePipeline = std::make_unique<MvePipeline>(
			mveDevice,
			"shaders/lattice_shader.vert.spv",
			"shaders/lattice_shader.frag.spv",
			pipelineConfig);
		mvePipeline->enableAlphaBlending(pipelineConfig);

	}

	
	void LatticeWireframeSystem::renderWireframe(FrameInfo& frameInfo) {
		mvePipeline->bind(frameInfo.commandBuffer);

		// The following error tells me I need to bind 
		// ONE descriptor set with BOTH bindings! Do not pass
		// a std::vector of descriptor sets.
		vkCmdBindDescriptorSets(
			frameInfo.commandBuffer,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			pipelineLayout,
			0,
			1,
			&frameInfo.descriptorSet,
			0,
			nullptr);
		
		for (auto& kv : frameInfo.gameObjects) {
			auto& obj = kv.second;
			if (obj.model == nullptr) continue; // Skip gameobject if it has no model (e.g. camera)
			SimplePushConstantData push{};
			auto modelMatrix = obj.transform.mat4();
			push.modelMatrix = modelMatrix;
			
			vkCmdPushConstants(
				frameInfo.commandBuffer,
				pipelineLayout,
				VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
				0,
				sizeof(SimplePushConstantData),
				&push);
			obj.model->bind(frameInfo.commandBuffer);
			obj.model->draw(frameInfo.commandBuffer);

		}

	}

}