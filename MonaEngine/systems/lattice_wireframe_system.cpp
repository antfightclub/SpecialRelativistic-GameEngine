#include "lattice_wireframe_system.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm.hpp>
#include <gtc/constants.hpp>

//std
#include <stdexcept>
#include <array>
#include <iostream>

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
			"./shaders/lattice_shader.vert.spv",
			"./shaders/lattice_shader.frag.spv",
			pipelineConfig);
		mvePipeline->enableAlphaBlending(pipelineConfig);

	}

	
	void LatticeWireframeSystem::renderWireframe(FrameInfo& frameInfo) {
		mvePipeline->bind(frameInfo.frameCommandBuffers.mainCommandBuffer);
		vkCmdBindDescriptorSets(
			frameInfo.frameCommandBuffers.mainCommandBuffer,
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
			/*std::cout << "model matrix: \n" << 
				modelMatrix[0][0] << ", " << modelMatrix[0][1] << ", " << modelMatrix[0][2] << ", " << modelMatrix[0][3] << "\n" <<
				modelMatrix[1][0] << ", " << modelMatrix[1][1] << ", " << modelMatrix[1][2] << ", " << modelMatrix[1][3] << "\n" <<
				modelMatrix[2][0] << ", " << modelMatrix[2][1] << ", " << modelMatrix[2][2] << ", " << modelMatrix[2][3] << "\n" <<
				modelMatrix[3][0] << ", " << modelMatrix[3][1] << ", " << modelMatrix[3][2] << ", " << modelMatrix[3][3] << "\n" 
				<< std::endl;*/
			
			vkCmdPushConstants(
				frameInfo.frameCommandBuffers.mainCommandBuffer,
				pipelineLayout,
				VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
				0,
				sizeof(SimplePushConstantData),
				&push);
			obj.model->bind(frameInfo.frameCommandBuffers.mainCommandBuffer);
			obj.model->draw(frameInfo.frameCommandBuffers.mainCommandBuffer);

		}

	}

}