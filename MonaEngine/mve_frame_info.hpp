#pragma once

#include "mve_camera.hpp"
#include "mve_game_object.hpp"

#include <vulkan/vulkan.h>
#include <vector>

namespace mve {

    # define MAX_LIGHTS 125

	//struct PointLight {
	//	glm::vec4 position{};  // ignore w in shader
	//	glm::vec4 color{}; // w is intensity
	//};

	//struct GlobalUbo {
	//	glm::mat4 projection{ 1.f };
	//	glm::mat4 view{ 1.f };
	//	glm::mat4 inverseView{1.f};
	//	glm::vec4 ambientLightColor{ 1.f, 1.f, 1.f, .02f }; // w is intensity
	//	PointLight pointLights[MAX_LIGHTS];
	//	int numLights;
	//};

	//struct PointLightUbo {
	//	PointLight pointLights[MAX_LIGHTS];
	//	glm::vec4 observerPosition;
	//	int numLights;
	//};

	struct GlobalUbo {
		glm::mat4 projection{ 1.f };
		glm::mat4 view{ 1.f };
		glm::mat4 inverseView{ 1.f };
		glm::vec4 ambientLightColor{ 1.f, 1.f, 1.f, .02f }; // w is intensity
		glm::vec4 observerPosition;
	};

	struct LatticeUbo {
		alignas(16) glm::vec3 Xp{0.f}; 
		alignas(16) glm::vec3 Xo{0.f};
		alignas(16) glm::mat4 Lorentz{1.f};
	};			   

	struct SpecialRelativityUbo {
		alignas(16) glm::mat4 Lorentz{ 0.f };
		alignas(16) glm::mat4 Lorentz_p2e{ 0.f }; // transform from "player to enemy" framë
		alignas(16) glm::mat4 Rotate{ 0.f };
		alignas(16) glm::vec4 dX{ 0.f };
		alignas(16) glm::vec4 xp{ 0.f };
	};
	
	struct FrameCommandBuffers {
		VkCommandBuffer mainCommandBuffer;
		VkCommandBuffer UICommandBuffer;
	};

	struct FrameInfo {
		int frameIndex;
		float frameTime;
		FrameCommandBuffers frameCommandBuffers;
		MveCamera& camera;
		VkDescriptorSet descriptorSet;
		MveGameObject::Map& gameObjects;
	};


} 