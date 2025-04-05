#pragma once

#include "mve_camera.hpp"
#include "mve_game_object.hpp"
#include "spacetimealgebra/mve_phasespace.hpp"
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
		glm::mat4 Lorentz{ 1.0f };
		glm::vec4 ambientLightColor{ 1.f, 1.f, 1.f, .02f }; // w is intensity
		glm::vec4 observerPosition{};
	};

	struct LatticeUbo {
		alignas(16) glm::vec3 Xp{0.f}; 
		alignas(16) glm::vec3 Xo{0.f};
		//alignas(16) glm::mat4 Lorentz{1.f};
	};			   

	struct SpecialRelativityUbo {
		alignas(16) glm::mat4 Lorentz_o2p{ 1.f };
		alignas(16) glm::mat4 Lorentz_p2o{ 1.f }; // transform from "player to object" frame
		alignas(16) glm::mat4 Rotate{ 1.f };
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

	struct GuiInfo {
		bool debug_open{};
		bool sta_open{};
		bool *render_lattice;
		bool *spawn_timeclocks;
		float frame_time{};
		float dt{};
		size_t amount_timeclocks;
		
		glm::mat4 view_matrix{ 1.f };
		glm::mat4 player_lorentz_boost{ 1.f };
		MvePhaseSpace PlayerPhaseSpace;
		MvePhaseSpace ObjectPhaseSpace;
		m4sta::mv diffpos;
		m4sta::mv x_p;
		m4sta::mv xp_playerframe;
	};


} 