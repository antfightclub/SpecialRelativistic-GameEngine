#pragma once

#include "mve_camera.hpp"
#include "mve_game_object.hpp"

#include <vulkan/vulkan.h>

namespace mve {
	struct FrameInfo {
		int frameIndex;
		int frameTime;
		VkCommandBuffer commandBuffer;
		MveCamera& camera;
		VkDescriptorSet globalDescriptorSet;
		MveGameObject::Map& gameObjects;
	};
} 