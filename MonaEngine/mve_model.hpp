#pragma once

#include "mve_device.hpp"
#include "mve_buffer.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm.hpp>

#include <memory>
#include <vector>

namespace mve {
	class MveModel {
	public:

		struct Vertex {
			glm::vec3 position{};
			glm::vec3 color{};
			glm::vec3 normal{};
			glm::vec2 uv{};

			static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
			static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();

			bool operator==(const Vertex& other) const {
				return position == other.position && color == other.color && normal == other.normal && uv == other.uv;
			}
		};

		struct Builder {
			std::vector<Vertex> vertices{};
			std::vector<uint32_t> indices{};

			void loadModelFromFile(const std::string& filepath);
			void loadModelFromStdVector(std::vector<glm::vec3>& vertices, std::vector<uint32_t>& indices);
		};

		MveModel(MveDevice &device, const MveModel::Builder &builder);
		~MveModel();

		MveModel(const MveModel&) = delete;
		MveModel& operator=(const MveModel&) = delete;

		static std::unique_ptr<MveModel> createModelFromFile(MveDevice& device, const std::string& filepath);
		static std::unique_ptr<MveModel> createModelFromStdVector(MveDevice& device, std::vector<glm::vec3>& vertices, std::vector<uint32_t>& indices);

		void bind(VkCommandBuffer commandBuffer);
		const void draw(VkCommandBuffer commandBuffer);

	private:
		void createVertexBuffers(const std::vector<Vertex>& vertices);
		void createIndexBuffers(const std::vector<uint32_t>& indices);

		MveDevice &mveDevice;

		std::unique_ptr<MveBuffer> vertexBuffer;
		uint32_t vertexCount;

		bool hasIndexBuffer = false;
		std::unique_ptr<MveBuffer> indexBuffer;
		uint32_t indexCount;
	};
	
}