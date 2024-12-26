#include "mve_descriptors.hpp"

// std
#include <cassert>
#include <stdexcept>

namespace mve {

    // *************** Descriptor Set Layout Builder *********************

    MveDescriptorSetLayout::Builder& MveDescriptorSetLayout::Builder::addBinding(
        uint32_t binding,
        VkDescriptorType descriptorType,
        VkShaderStageFlags stageFlags,
        uint32_t count) {
        assert(bindings.count(binding) == 0 && "Binding already in use");
        VkDescriptorSetLayoutBinding layoutBinding{};
        layoutBinding.binding = binding;
        layoutBinding.descriptorType = descriptorType;
        layoutBinding.descriptorCount = count;
        layoutBinding.stageFlags = stageFlags;
        bindings[binding] = layoutBinding;
        return *this;
    }

    std::unique_ptr<MveDescriptorSetLayout> MveDescriptorSetLayout::Builder::build() const {
        return std::make_unique<MveDescriptorSetLayout>(mveDevice, bindings);
    }

    // *************** Descriptor Set Layout *********************

    MveDescriptorSetLayout::MveDescriptorSetLayout(
        MveDevice& mveDevice, std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings)
        : mveDevice{ mveDevice }, bindings{ bindings } {
        std::vector<VkDescriptorSetLayoutBinding> setLayoutBindings{};
        for (auto kv : bindings) {
            setLayoutBindings.push_back(kv.second);
        }

        VkDescriptorSetLayoutCreateInfo descriptorSetLayoutInfo{};
        descriptorSetLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        descriptorSetLayoutInfo.bindingCount = static_cast<uint32_t>(setLayoutBindings.size());
        descriptorSetLayoutInfo.pBindings = setLayoutBindings.data();


        if (vkCreateDescriptorSetLayout(
            mveDevice.device(),
            &descriptorSetLayoutInfo,
            nullptr,
            &descriptorSetLayout) != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor set layout!");
        }
    }

    MveDescriptorSetLayout::~MveDescriptorSetLayout() {
        vkDestroyDescriptorSetLayout(mveDevice.device(), descriptorSetLayout, nullptr);
    }

    // *************** Descriptor Pool Builder *********************

    MveDescriptorPool::Builder& MveDescriptorPool::Builder::addPoolSize(
        VkDescriptorType descriptorType, uint32_t count) {
        poolSizes.push_back({ descriptorType, count });
        return *this;
    }

    MveDescriptorPool::Builder& MveDescriptorPool::Builder::setPoolFlags(
        VkDescriptorPoolCreateFlags flags) {
        poolFlags = flags;
        return *this;
    }
    MveDescriptorPool::Builder& MveDescriptorPool::Builder::setMaxSets(uint32_t count) {
        maxSets = count;
        return *this;
    }

    std::unique_ptr<MveDescriptorPool> MveDescriptorPool::Builder::build() const {
        return std::make_unique<MveDescriptorPool>(mveDevice, maxSets, poolFlags, poolSizes);
    }

    // *************** Descriptor Pool *********************

    MveDescriptorPool::MveDescriptorPool(
        MveDevice& mveDevice,
        uint32_t maxSets,
        VkDescriptorPoolCreateFlags poolFlags,
        const std::vector<VkDescriptorPoolSize>& poolSizes)
        : mveDevice{ mveDevice } {
        VkDescriptorPoolCreateInfo descriptorPoolInfo{};
        descriptorPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        descriptorPoolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
        descriptorPoolInfo.pPoolSizes = poolSizes.data();
        descriptorPoolInfo.maxSets = maxSets;
        descriptorPoolInfo.flags = poolFlags;

        if (vkCreateDescriptorPool(mveDevice.device(), &descriptorPoolInfo, nullptr, &descriptorPool) !=
            VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor pool!");
        }
    }

    MveDescriptorPool::~MveDescriptorPool() {
        vkDestroyDescriptorPool(mveDevice.device(), descriptorPool, nullptr);
    }

    bool MveDescriptorPool::allocateDescriptor(
        const VkDescriptorSetLayout descriptorSetLayout, VkDescriptorSet& descriptor) const {
        VkDescriptorSetAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = descriptorPool;
        allocInfo.pSetLayouts = &descriptorSetLayout;
        allocInfo.descriptorSetCount = 2;

        // Might want to create a "DescriptorPoolManager" class that handles this case, and builds
        // a new pool whenever an old pool fills up. But this is beyond our current scope
        if (vkAllocateDescriptorSets(mveDevice.device(), &allocInfo, &descriptor) != VK_SUCCESS) {
            return false;
        }
        return true;
    }

    void MveDescriptorPool::freeDescriptors(std::vector<VkDescriptorSet>& descriptors) const {
        vkFreeDescriptorSets(
            mveDevice.device(),
            descriptorPool,
            static_cast<uint32_t>(descriptors.size()),
            descriptors.data());
    }

    void MveDescriptorPool::resetPool() {
        vkResetDescriptorPool(mveDevice.device(), descriptorPool, 0);
    }

    // *************** Descriptor Writer *********************

    MveDescriptorWriter::MveDescriptorWriter(MveDescriptorSetLayout& setLayout, MveDescriptorPool& pool)
        : setLayout{ setLayout }, pool{ pool } {
    }

    MveDescriptorWriter& MveDescriptorWriter::writeBuffer(
        uint32_t binding, VkDescriptorBufferInfo* bufferInfo) {
        assert(setLayout.bindings.count(binding) == 1 && "Layout does not contain specified binding");

        auto& bindingDescription = setLayout.bindings[binding];

        assert(
            bindingDescription.descriptorCount == 1 &&
            "Binding single descriptor info, but binding expects multiple");

        VkWriteDescriptorSet write{};
        write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        write.descriptorType = bindingDescription.descriptorType;
        write.dstBinding = binding;
        write.pBufferInfo = bufferInfo;
        write.descriptorCount = 1;

        writes.push_back(write);
        return *this;
    }

    MveDescriptorWriter& MveDescriptorWriter::writeImage(
        uint32_t binding, VkDescriptorImageInfo* imageInfo) {
        assert(setLayout.bindings.count(binding) == 1 && "Layout does not contain specified binding");

        auto& bindingDescription = setLayout.bindings[binding];

        assert(
            bindingDescription.descriptorCount == 1 &&
            "Binding single descriptor info, but binding expects multiple");

        VkWriteDescriptorSet write{};
        write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        write.descriptorType = bindingDescription.descriptorType;
        write.dstBinding = binding;
        write.pImageInfo = imageInfo;
        write.descriptorCount = 1;

        writes.push_back(write);
        return *this;
    }

    bool MveDescriptorWriter::build(VkDescriptorSet& set) {
        bool success = pool.allocateDescriptor(setLayout.getDescriptorSetLayout(), set);
        if (!success) {
            return false;
        }
        overwrite(set);
        return true;
    }

    void MveDescriptorWriter::overwrite(VkDescriptorSet& set) {
        for (auto& write : writes) {
            write.dstSet = set;
        }
        vkUpdateDescriptorSets(pool.mveDevice.device(), writes.size(), writes.data(), 0, nullptr);
    }

}  // namespace mve
