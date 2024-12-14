#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


class VulkanEngine {
public:
	bool _isInitialized{ false };
	int _frameNumber{ 0 };
	VkExtent2D _windowExtent{ 800, 600 };

	struct GLFW_Window* _window{ nullptr };

	static VulkanEngine& Get();

	void init();
	void cleanup();
	void draw();
	void run();

};