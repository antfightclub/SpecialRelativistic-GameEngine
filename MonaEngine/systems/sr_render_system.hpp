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
	class SRRenderSystem {
	public:

		SRRenderSystem(MveDevice& device, VkRenderPass renderPass, VkDescriptorSetLayout descriptorSetLayout);
		~SRRenderSystem();

		SRRenderSystem(const SRRenderSystem&) = delete;
		SRRenderSystem& operator=(const SRRenderSystem&) = delete;

		void render(FrameInfo& frameInfo, unsigned int NOTid);

	private:
		void createPipelineLayout(VkDescriptorSetLayout globalDescriptorSetLayout);
		void createPipeline(VkRenderPass renderPass);

		MveDevice& mveDevice;

		std::unique_ptr<MvePipeline> mvePipeline;
		VkPipelineLayout pipelineLayout;
	};
}