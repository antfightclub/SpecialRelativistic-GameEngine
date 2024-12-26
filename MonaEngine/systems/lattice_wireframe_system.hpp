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

		LatticeWireframeSystem(MveDevice& device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout);
		~LatticeWireframeSystem();

		LatticeWireframeSystem(const LatticeWireframeSystem&) = delete;
		LatticeWireframeSystem& operator=(const LatticeWireframeSystem&) = delete;

		void renderWireframe(FrameInfo& frameInfo);

	private:
		void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);
		void createPipeline(VkRenderPass renderPass);

		MveDevice& mveDevice;

		std::unique_ptr<MvePipeline> mvePipeline;
		VkPipelineLayout pipeLineLayout;
	};
}