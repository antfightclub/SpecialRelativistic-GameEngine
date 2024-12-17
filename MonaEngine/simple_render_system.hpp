#pragma once

#include "mve_camera.hpp"
#include "mve_pipeline.hpp"
#include "mve_game_object.hpp"
#include "mve_device.hpp"

//std
#include <memory>
#include <vector>

namespace mve {

	class SimpleRenderSystem {

	public:


		SimpleRenderSystem(MveDevice& device, VkRenderPass renderPass);
		~SimpleRenderSystem();

		SimpleRenderSystem(const SimpleRenderSystem&) = delete;
		SimpleRenderSystem& operator=(const SimpleRenderSystem&) = delete;

		void renderGameObjects(VkCommandBuffer commandBuffer, std::vector<MveGameObject> &gameObjects, const MveCamera& camera);

	private:

		void createPipelineLayout();
		void createPipeline(VkRenderPass renderPass);
		


		MveDevice& mveDevice;

		std::unique_ptr<MvePipeline> mvePipeline;
		VkPipelineLayout pipelineLayout;
	};
}