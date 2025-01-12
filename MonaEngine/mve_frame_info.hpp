#pragma once

#include "mve_camera.hpp"
#include "mve_game_object.hpp"

#include <vulkan/vulkan.h>
#include <vector>

namespace mve {

# define MAX_LIGHTS 10

	struct PointLight {
		glm::vec4 position{};  // ignore w
		glm::vec4 color{}; // w is intensity
	};

	//struct GlobalUbo {
	//	glm::mat4 projection{ 1.f };
	//	glm::mat4 view{ 1.f };
	//	glm::mat4 inverseView{1.f};
	//	glm::vec4 ambientLightColor{ 1.f, 1.f, 1.f, .02f }; // w is intensity
	//	PointLight pointLights[MAX_LIGHTS];
	//	int numLights;
	//};

	struct GlobalUbo {
		glm::mat4 projection{ 1.f };
		glm::mat4 view{ 1.f };
		glm::mat4 inverseView{ 1.f };
		glm::vec4 ambientLightColor{ 1.f, 1.f, 1.f, .02f }; // w is intensity
	};

	struct LatticeUbo {
		alignas(16) glm::vec3 Xp{0.f}; 
		alignas(16) glm::vec3 Xo{0.f};
		alignas(16) glm::mat4 Lorentz{1.f};
		alignas(16) glm::mat4 invLorentz{ 1.f };
	};			   
	
	struct FrameCommandBuffers {
		VkCommandBuffer mainCommandBuffer;
		VkCommandBuffer UICommandBuffer;
	};

	struct FrameInfo {
		int frameIndex;
		float frameTime;
		//VkCommandBuffer commandBuffer;
		FrameCommandBuffers frameCommandBuffers;
		MveCamera& camera;
		VkDescriptorSet descriptorSet;
		//VkDescriptorSet latticeDescriptorSet;
		MveGameObject::Map& gameObjects;
	};


} 