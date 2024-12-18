#include "mve_model.hpp"
#include "mve_utils.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/hash.hpp>

#include <cassert>
#include <cstring>
#include <unordered_map>

namespace std {
	template<>
	struct hash<mve::MveModel::Vertex> {
		size_t operator()(mve::MveModel::Vertex const& vertex) const {
			size_t seed = 0;
			mve::hashCombine(seed, vertex.position, vertex.color, vertex.normal, vertex.uv);
			return seed;
		}
	};
}

namespace mve {

	MveModel::MveModel(MveDevice &device, const MveModel::Builder &builder) : mveDevice{ device } {
		createVertexBuffers(builder.vertices);
		createIndexBuffers(builder.indices);

	}

	MveModel::~MveModel() {
		vkDestroyBuffer(mveDevice.device(), vertexBuffer, nullptr);
		vkFreeMemory(mveDevice.device(), vertexBufferMemory, nullptr);

		if (hasIndexBuffer) {
			vkDestroyBuffer(mveDevice.device(), indexBuffer, nullptr);
			vkFreeMemory(mveDevice.device(), indexBufferMemory, nullptr);
		}

	}

	std::unique_ptr<MveModel> MveModel::createModelFromFile(MveDevice& device, const std::string& filepath) {
		Builder builder{};
		builder.loadModel(filepath);
		return std::make_unique<MveModel>(device, builder);
	}
	
	void MveModel::createVertexBuffers(const std::vector<Vertex>& vertices) {
		vertexCount = static_cast<uint32_t>(vertices.size());
		assert(vertexCount >= 3 && "Vertex count must be at least 3!");
		VkDeviceSize bufferSize = sizeof(vertices[0]) * vertexCount;

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;

		mveDevice.createBuffer(
			bufferSize,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			stagingBuffer,
			stagingBufferMemory);

		void* data;
		vkMapMemory(mveDevice.device(), stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, vertices.data(), static_cast<size_t>(bufferSize));
		vkUnmapMemory(mveDevice.device(), stagingBufferMemory);

		mveDevice.createBuffer(
			bufferSize,
			VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			vertexBuffer,
			vertexBufferMemory);

		mveDevice.copyBuffer(stagingBuffer, vertexBuffer, bufferSize);

		vkDestroyBuffer(mveDevice.device(), stagingBuffer, nullptr);
		vkFreeMemory(mveDevice.device(), stagingBufferMemory, nullptr);

	}

	void MveModel::createIndexBuffers(const std::vector<uint32_t>& indices) {
		indexCount = static_cast<uint32_t>(indices.size());
		hasIndexBuffer = indexCount > 0;

		if (!hasIndexBuffer) {
			return;
		}
		
		VkDeviceSize bufferSize = sizeof(indices[0]) * indexCount;

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;
		mveDevice.createBuffer(
			bufferSize,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			stagingBuffer,
			stagingBufferMemory);

		void* data;
		vkMapMemory(mveDevice.device(), stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, indices.data(), static_cast<size_t>(bufferSize));
		vkUnmapMemory(mveDevice.device(), stagingBufferMemory);

		mveDevice.createBuffer(
			bufferSize,
			VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			indexBuffer,
			indexBufferMemory);

		mveDevice.copyBuffer(stagingBuffer, indexBuffer, bufferSize);

		vkDestroyBuffer(mveDevice.device(), stagingBuffer, nullptr);
		vkFreeMemory(mveDevice.device(), stagingBufferMemory, nullptr);


	}

	void MveModel::draw(VkCommandBuffer commandBuffer) {
		if (hasIndexBuffer) {
			vkCmdDrawIndexed(commandBuffer, indexCount, 1, 0, 0, 0);
		}
		else {
			vkCmdDraw(commandBuffer, vertexCount, 1, 0, 0);
		}
	}

	void MveModel::bind(VkCommandBuffer commandBuffer) {
		VkBuffer buffers[] = { vertexBuffer };
		VkDeviceSize offsets[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);

		if (hasIndexBuffer) {
			vkCmdBindIndexBuffer(commandBuffer, indexBuffer, 0, VK_INDEX_TYPE_UINT32);
		}
	}

	std::vector<VkVertexInputBindingDescription> MveModel::Vertex::getBindingDescriptions() {
		std::vector<VkVertexInputBindingDescription> bindingDescriptions(1);
		bindingDescriptions[0].binding = 0;
		bindingDescriptions[0].stride = sizeof(Vertex);
		bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		return bindingDescriptions;
	}

	std::vector<VkVertexInputAttributeDescription> MveModel::Vertex::getAttributeDescriptions() {
		std::vector<VkVertexInputAttributeDescription> attributeDescriptions(2);
		
		// MveModel::Vertex::position
		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, position);

		// MveModel::Vertex::color
		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);


		return attributeDescriptions;
	}

	void MveModel::Builder::loadModel(const std::string& filepath) {
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warn, err;

		if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filepath.c_str())) {
			throw std::runtime_error(warn + err);
		}

		vertices.clear();
		indices.clear();

		std::unordered_map<Vertex, uint32_t> uniqueVertices{};
		for (const auto& shape : shapes) {
			for (const auto& index : shape.mesh.indices) {
				Vertex vertex{};

				if (index.vertex_index >= 0) {
					vertex.position = {
						attrib.vertices[3 * index.vertex_index + 0],
						attrib.vertices[3 * index.vertex_index + 1],
						attrib.vertices[3 * index.vertex_index + 2]
					};

					auto colorIndex = 3 * index.vertex_index + 2;
					if (colorIndex < attrib.colors.size()) {
						vertex.color = {
							attrib.colors[colorIndex - 2],
							attrib.colors[colorIndex - 1],
							attrib.colors[colorIndex - 0]
						};
					}
					else {
						vertex.color = { 1.f, 1.f, 1.f }; // Default color
					}
				}

				if (index.normal_index >= 0) {
					vertex.normal = {
						attrib.normals[3 * index.normal_index + 0],
						attrib.normals[3 * index.normal_index + 1],
						attrib.normals[3 * index.normal_index + 2]
					};
				}

				if (index.texcoord_index >= 0) {
					vertex.uv = {
						attrib.texcoords[2 * index.texcoord_index + 0],
						attrib.texcoords[2 * index.texcoord_index + 1]
					};
				}

				if (uniqueVertices.count(vertex) == 0) {
					uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
					vertices.push_back(vertex);
				}
				indices.push_back(uniqueVertices[vertex]);

			}
		}

	}

}