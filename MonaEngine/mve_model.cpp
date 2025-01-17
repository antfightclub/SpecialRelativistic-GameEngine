#include "mve_model.hpp"
#include "mve_utils.hpp"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/hash.hpp>

#include <cassert>
#include <cstring>
#include <unordered_map>
#include <iostream>

// Use an unordeered map of gameobjects; game object ID's are pretty much just sequential
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

	MveModel::~MveModel() {}

	std::unique_ptr<MveModel> MveModel::createModelFromFile(MveDevice& device, const std::string& filepath) {
		Builder builder{};
		builder.loadModelFromFile(filepath);
		return std::make_unique<MveModel>(device, builder);
	}
	
	std::unique_ptr<MveModel> MveModel::createModelFromStdVector(MveDevice& device, std::vector<glm::vec3>& vertices, std::vector<uint32_t>& indices) {
		Builder builder{};
		builder.loadModelFromStdVector(vertices, indices);
		return std::make_unique<MveModel>(device, builder);
	}

	std::unique_ptr<MveModel> MveModel::createDebuggingModel(MveDevice& device) {
		Builder builder{};
		builder.loadDebugModel();
		return std::make_unique <MveModel>(device, builder);
	}

	void MveModel::createVertexBuffers(const std::vector<Vertex>& vertices) {
		vertexCount = static_cast<uint32_t>(vertices.size());
		assert(vertexCount >= 3 && "Vertex count must be at least 3!");
		VkDeviceSize bufferSize = sizeof(vertices[0]) * vertexCount;
		uint32_t vertexSize = sizeof(vertices[0]);

		MveBuffer stagingBuffer{
			mveDevice,
			vertexSize,
			vertexCount,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		};

		stagingBuffer.map();
		stagingBuffer.writeToBuffer((void*)vertices.data());

		vertexBuffer = std::make_unique<MveBuffer>(
			mveDevice,
			vertexSize,
			vertexCount,
			VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
		);

		VkCommandPool cmdPool = mveDevice.getCommandPool();
		mveDevice.copyBuffer(stagingBuffer.getBuffer(), vertexBuffer->getBuffer(), bufferSize, cmdPool);
	}

	void MveModel::createIndexBuffers(const std::vector<uint32_t>& indices) {
		indexCount = static_cast<uint32_t>(indices.size());
		hasIndexBuffer = indexCount > 0;

		if (!hasIndexBuffer) {
			return;
		}
		
		VkDeviceSize bufferSize = sizeof(indices[0]) * indexCount;
		uint32_t indexSize = sizeof(indices[0]);

		MveBuffer stagingBuffer{
			mveDevice,
			indexSize,
			indexCount,
			VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
		};

		stagingBuffer.map();
		stagingBuffer.writeToBuffer((void*)indices.data());

		indexBuffer = std::make_unique<MveBuffer>(
			mveDevice,
			indexSize,
			indexCount,
			VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
			VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
		);
		VkCommandPool cmdPool = mveDevice.getCommandPool();
		mveDevice.copyBuffer(stagingBuffer.getBuffer(), indexBuffer->getBuffer(), bufferSize, cmdPool);
	}

	const void MveModel::draw(VkCommandBuffer commandBuffer) {
		if (hasIndexBuffer) {
			vkCmdDrawIndexed(commandBuffer, indexCount, 1, 0, 0, 0);
		}
		else {
			vkCmdDraw(commandBuffer, vertexCount, 1, 0, 0);
		}
	}

	void MveModel::bind(VkCommandBuffer commandBuffer) {
		VkBuffer buffers[] = { vertexBuffer->getBuffer() };
		VkDeviceSize offsets[] = { 0 };
		vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offsets);

		if (hasIndexBuffer) {
			vkCmdBindIndexBuffer(commandBuffer, indexBuffer->getBuffer(), 0, VK_INDEX_TYPE_UINT32);
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
		std::vector<VkVertexInputAttributeDescription> attributeDescriptions{};
		
		attributeDescriptions.push_back({ 0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, position) });
		attributeDescriptions.push_back({ 1, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, color)    });
		attributeDescriptions.push_back({ 2, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, normal)   });
		attributeDescriptions.push_back({ 3, 0, VK_FORMAT_R32G32_SFLOAT,    offsetof(Vertex, uv)       });
		return attributeDescriptions;
	}

	// Loads .obj files from a given file-path.
	void MveModel::Builder::loadModelFromFile(const std::string& filepath) {
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
					
					
					vertex.color = {
						attrib.colors[3 * index.vertex_index + 0],
						attrib.colors[3 * index.vertex_index + 1],
						attrib.colors[3 * index.vertex_index + 2]
					};
					
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

	// Provided vertices and indices, make game object with those vertices
	// Currently used by the lattice line renderer, but supposing that the 
	// given std::vectors are valid given a primitive type, it should work
	void MveModel::Builder::loadModelFromStdVector(std::vector<glm::vec3>& verts, std::vector<uint32_t>& indcs) {
		vertices.clear();
		indices.clear();

		// This method is used mainly for the lattice, and it provides its own index vector
		// Therefore this method does not check for unique vertices
		for (const auto& vert : verts) {

			Vertex vertex{};
			vertex.position = vert;
			vertex.color = { .5f, .5f, .5f};
			// For the lattice, the normals and uv's are unused, since it's a line-renderer
			vertex.normal = {1.0f, 1.0f, 1.0f};
			vertex.uv = {1.0f, 1.0f};

			vertices.push_back(vertex);
		}

		for (const auto& indc : indcs) {
			indices.push_back(indc);
		}
	}

	// Create a simple axis object with some defined colors for what points in what axis.
	void MveModel::Builder::loadDebugModel() {
		vertices.clear();
		indices.clear();
		
		// Origin: white color
		Vertex base{};
		base.position = { 0.0, 0.0, 0.0 };
		base.color = { 1.f, 1.f, 1.f };
		
		Vertex up{};
		up.position = { 0.0, 1.0, 0.0 }; // Y is up, but this is flipped in Vulkan due to its conventions
		up.color = { 0.f, 1.f, 0.f };	 // Green is up

		// Nudges show which vector is a basis vector
		Vertex upNudge{};
		upNudge.position = { 0.1, 0.75, 0.1 };
		upNudge.color = { 0.f, 1.f, 0.f };
				
		Vertex down{}; 
		down.position = { 0.0, -1.0, 0.0 }; // Y up system, but this is flipped in Vulkan due to its conventions
		down.color = { 0.f, 1.f, 0.f };	 // Green is down
		
		Vertex right{};
		right.position = { 1.0, 0.0, 0.0 };  // right
		right.color = { 1.f, 0.f, 0.f };	 // red is right
		
		Vertex rightNudge{};
		rightNudge.position = { .75, .1, .1 };
		rightNudge.color = { 1.f, 0.f, 0.f };

		Vertex left{};
		left.position = { -1.0, 0.0, 0.0 };  // right
		left.color = { 1.f, 0.f, 0.f };	 // red is left

		Vertex forward{}; 
		forward.position = { 0.0, 0.0, 1.0 };  // forward
		forward.color = { 0.f, 0.f, 1.f };	 // blue is forwad

		Vertex forwardNudge{};
		forwardNudge.position = { .1, .1, .75 };
		forwardNudge.color = { 0.f, 0.f, 1.f };
	
		Vertex backward{};
		backward.position = { 0.0, 0.0, -1.0 };  // forward
		backward.color = { 0.f, 0.f, 1.f };	 // blue is backward
		
		vertices.push_back(base);			// 0
		vertices.push_back(up);				// 1
		vertices.push_back(down);			// 2
		vertices.push_back(right);			// 3
		vertices.push_back(left);			// 4
		vertices.push_back(forward);		// 5
		vertices.push_back(backward);		// 6
		vertices.push_back(upNudge);		// 7
		vertices.push_back(rightNudge);		// 8
		vertices.push_back(forwardNudge);	// 9

		// Up + up nudge
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(1);
		indices.push_back(7);

		// Down
		indices.push_back(0);
		indices.push_back(2);
		
		// Right + right nudge
		indices.push_back(0);
		indices.push_back(3);
		indices.push_back(3);
		indices.push_back(8);

		// Left
		indices.push_back(0);
		indices.push_back(4);
		
		// Forward + forward nudge
		indices.push_back(0);
		indices.push_back(5);
		indices.push_back(5);
		indices.push_back(9);

		// Backward
		indices.push_back(0);
		indices.push_back(6);
	}
}