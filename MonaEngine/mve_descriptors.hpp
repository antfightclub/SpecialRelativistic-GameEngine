#pragma once

#include "mve_device.hpp"

#include <memory>
#include <unordered_map>
#include <vector>

namespace mve {
	
    class MveDescriptorSetLayout {
    public:
        class Builder {
        public:
            Builder(MveDevice& mveDevice) : mveDevice{ mveDevice } {}

            // This adds a descriptor set layout (used as a blueprint during pipeline creation)
            Builder& addBinding(
                uint32_t binding,
                VkDescriptorType descriptorType,
                VkShaderStageFlags stageFlags,
                uint32_t count = 1);
            std::unique_ptr<MveDescriptorSetLayout> build() const;

        private:
            MveDevice& mveDevice;
            std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings{};
        };

        MveDescriptorSetLayout(
            MveDevice& mveDevice, std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings);
        ~MveDescriptorSetLayout();
        MveDescriptorSetLayout(const MveDescriptorSetLayout&) = delete;
        MveDescriptorSetLayout& operator=(const MveDescriptorSetLayout&) = delete;

        VkDescriptorSetLayout getDescriptorSetLayout() const { return descriptorSetLayout; }

    private:
        MveDevice& mveDevice;
        VkDescriptorSetLayout descriptorSetLayout;
        std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings;

        friend class MveDescriptorWriter;
    };

    class MveDescriptorPool {
    public:
        class Builder {
        public:
            Builder(MveDevice& mveDevice) : mveDevice{ mveDevice } {}

            Builder& addPoolSize(VkDescriptorType descriptorType, uint32_t count);
            Builder& setPoolFlags(VkDescriptorPoolCreateFlags flags);
            Builder& setMaxSets(uint32_t count);
            std::unique_ptr<MveDescriptorPool> build() const;

        private:
            MveDevice& mveDevice;
            std::vector<VkDescriptorPoolSize> poolSizes{};
            uint32_t maxSets = 1000;
            VkDescriptorPoolCreateFlags poolFlags = 0;
        };

        MveDescriptorPool(
            MveDevice& mveDevice,
            uint32_t maxSets,
            VkDescriptorPoolCreateFlags poolFlags,
            const std::vector<VkDescriptorPoolSize>& poolSizes);
        ~MveDescriptorPool();
        MveDescriptorPool(const MveDescriptorPool&) = delete;
        MveDescriptorPool& operator=(const MveDescriptorPool&) = delete;

        bool allocateDescriptor(
            const VkDescriptorSetLayout descriptorSetLayout, VkDescriptorSet& descriptor) const;

        void freeDescriptors(std::vector<VkDescriptorSet>& descriptors) const;

        void resetPool();

    private:
        MveDevice& mveDevice;
        VkDescriptorPool descriptorPool = VK_NULL_HANDLE;

        friend class MveDescriptorWriter;
    };

    class MveDescriptorWriter {
    public:
        MveDescriptorWriter(MveDescriptorSetLayout& setLayout, MveDescriptorPool& pool);

        MveDescriptorWriter& writeBuffer(uint32_t binding, VkDescriptorBufferInfo* bufferInfo);
        MveDescriptorWriter& writeImage(uint32_t binding, VkDescriptorImageInfo* imageInfo);

        bool build(VkDescriptorSet& set);
        void overwrite(VkDescriptorSet& set);

    private:
        MveDescriptorSetLayout& setLayout;
        MveDescriptorPool& pool;
        std::vector<VkWriteDescriptorSet> writes;
    };

}