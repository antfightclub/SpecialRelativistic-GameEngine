#pragma once

#include "mve_device.hpp"

// std
#include <string>
#include <vector>

namespace mve {

	struct PipelineConfigInfo {};

	class MvePipeline {

	public:
		MvePipeline(
			MveDevice &device, 
			const std::string& vertFilepath, 
			const std::string& fragFilepath, 
			const PipelineConfigInfo& configInfo);

		~MvePipeline() {}

		MvePipeline(const MvePipeline&) = delete;
		void operator=(const MvePipeline&) = delete;

		static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);

	private:
		static std::vector<char> readFile(const std::string& filepath);

		void createGraphicsPipeline(
			const std::string& vertFilepath, 
			const std::string& fragFilepath,
			const PipelineConfigInfo& configInfo);

		void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

		MveDevice& mveDevice;
		VkPipeline graphicsPipeline;
		VkShaderModule vertShaderModule;
		VkShaderModule fragShaderModule;
	};
	
}