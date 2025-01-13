#pragma once

#include "mve_device.hpp"

// vulkan headers
#include <vulkan/vulkan.h>

// std lib headers
#include <memory>
#include <string>
#include <vector>

namespace mve {

class MveSwapChain {
 public:
  static constexpr int MAX_FRAMES_IN_FLIGHT = 2;

  MveSwapChain(MveDevice &deviceRef, VkExtent2D windowExtent);
  MveSwapChain(MveDevice& deviceRef, VkExtent2D windowExtent, std::shared_ptr<MveSwapChain> previous);
  ~MveSwapChain();

  MveSwapChain(const MveSwapChain &) = delete;
  MveSwapChain &operator=(const MveSwapChain &) = delete;

  VkFramebuffer getFrameBuffer(int index) { return swapChainFramebuffers[index]; }
  VkFramebuffer getUIFrameBuffer(int index) { return UIFramebuffers[index]; }
  VkRenderPass getRenderPass() { return renderPass; }
  VkRenderPass getUIRenderPass() { return imguiRenderPass; }
  VkImageView getImageView(int index) { return swapChainImageViews[index]; }
  size_t imageCount() { return swapChainImages.size(); }
  //size_t uiImageCount() { return imguiImages.size(); }
  VkFormat getSwapChainImageFormat() { return swapChainImageFormat; }
  VkExtent2D getSwapChainExtent() { return swapChainExtent; }
  uint32_t width() { return swapChainExtent.width; }
  uint32_t height() { return swapChainExtent.height; }

  float extentAspectRatio() {
    return static_cast<float>(swapChainExtent.width) / static_cast<float>(swapChainExtent.height);
  }
  VkFormat findDepthFormat();

  VkResult acquireNextImage(uint32_t *imageIndex);
  VkResult submitCommandBuffers(const std::array<VkCommandBuffer,2> *buffers, uint32_t *imageIndex);

  bool compareSwapFormats(const MveSwapChain& swapChain) const {
      return swapChain.swapChainDepthFormat == swapChainDepthFormat && swapChain.swapChainImageFormat == swapChainImageFormat;
  }

  VkFormat getDepthFormat() { return swapChainDepthFormat; }
  

 private:
  void init();
  void createSwapChain();
  void createImageViews();
  void createDepthResources();
  void createRenderPass();
  void createUIRenderPass();
  void createFramebuffers();
  void createUIFrameBuffers();
  void createSyncObjects();

  // Helper functions
  VkSurfaceFormatKHR chooseSwapSurfaceFormat(
      const std::vector<VkSurfaceFormatKHR> &availableFormats);
  VkPresentModeKHR chooseSwapPresentMode(
      const std::vector<VkPresentModeKHR> &availablePresentModes);
  VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

  VkFormat swapChainImageFormat;
  VkFormat swapChainDepthFormat;
  VkExtent2D swapChainExtent;

  std::vector<VkFramebuffer> swapChainFramebuffers;
  std::vector<VkFramebuffer> UIFramebuffers;
  VkRenderPass renderPass;
  VkRenderPass imguiRenderPass;

  std::vector<VkImage> depthImages;
  std::vector<VkDeviceMemory> depthImageMemorys;
  std::vector<VkImageView> depthImageViews;
  std::vector<VkImage> swapChainImages;
  std::vector<VkImageView> swapChainImageViews;

  MveDevice &device;
  VkExtent2D windowExtent;

  VkSwapchainKHR swapChain;
  std::shared_ptr<MveSwapChain> oldSwapChain;

  std::vector<VkSemaphore> imageAvailableSemaphores;
  std::vector<VkSemaphore> renderFinishedSemaphores;
  std::vector<VkFence> inFlightFences;
  std::vector<VkFence> imagesInFlight;
  size_t currentFrame = 0;
};

}  // namespace lve
