#include "lattice_wireframe_system.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm.hpp>
#include <gtc/constants.hpp>

//std
#include <stdexcept>
#include <array>

namespace mve {
	
	LatticeWireframeSystem::LatticeWireframeSystem(MveDevice& device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout) : mveDevice{ device } {
		//createpipelinelayout pass globalsetlayout
		//createpipeline pass renderpass
	}

	LatticeWireframeSystem::~LatticeWireframeSystem() { vkDestroyPipelineLayout(mveDevice.device(), pipeLineLayout, nullptr); }

	void LatticeWireframeSystem::createPipelineLayout(VkDescriptorSetLayout globalSetLayout) {

	}

	void LatticeWireframeSystem::createPipeline(VkRenderPass renderPass) {

	}

	void LatticeWireframeSystem::renderWireframe(FrameInfo& frameInfo) {

	}

}