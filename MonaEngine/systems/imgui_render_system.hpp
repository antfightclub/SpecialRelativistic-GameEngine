#pragma once

#include "../mve_camera.hpp"
#include "../mve_pipeline.hpp"
#include "../mve_game_object.hpp"
#include "../mve_device.hpp"
#include "../mve_frame_info.hpp"

//std
#include <memory>
#include <vector>


// Note: Is not currently in use.

namespace mve {
	class ImguiRenderSystem {
	public:

		ImguiRenderSystem(MveDevice& device, VkRenderPass renderPass, VkDescriptorSetLayout descriptorSetLayout);
		~ImguiRenderSystem();

		ImguiRenderSystem(const ImguiRenderSystem&) = delete;
		ImguiRenderSystem& operator=(const ImguiRenderSystem&) = delete;

		void renderImgui(FrameInfo& frameInfo);

	private:
		// "global" here refers to the "GlobalUbo" defined in mve::FrameInfo::GlobalUbo
		void createPipelineLayout(VkDescriptorSetLayout descriptorSetLayout);
		void createPipeline(VkRenderPass renderPass);

		MveDevice& mveDevice;

		std::unique_ptr<MvePipeline> mvePipeline;
		VkPipelineLayout pipelineLayout;
	};
}