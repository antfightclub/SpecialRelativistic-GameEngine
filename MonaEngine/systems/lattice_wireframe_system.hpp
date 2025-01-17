#pragma once

#include "../mve_camera.hpp"
#include "../mve_pipeline.hpp"
#include "../mve_game_object.hpp"
#include "../mve_device.hpp"
#include "../mve_frame_info.hpp"

//std
#include <memory>
#include <vector>

namespace mve {
	class LatticeWireframeSystem {
	public:

		LatticeWireframeSystem(MveDevice& device, VkRenderPass renderPass, VkDescriptorSetLayout descriptorSetLayout);
		~LatticeWireframeSystem();

		LatticeWireframeSystem(const LatticeWireframeSystem&) = delete;
		LatticeWireframeSystem& operator=(const LatticeWireframeSystem&) = delete;

		void renderWireframe(FrameInfo& frameInfo, unsigned int id); // MveGameObject id

	private:
		// "global" here refers to the "GlobalUbo" defined in mve::FrameInfo::GlobalUbo
		void createPipelineLayout(VkDescriptorSetLayout globalDescriptorSetLayout);
		void createPipeline(VkRenderPass renderPass);

		MveDevice& mveDevice;

		std::unique_ptr<MvePipeline> mvePipeline;
		VkPipelineLayout pipelineLayout;
	};
}