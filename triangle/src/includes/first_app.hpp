#pragma once

#include <memory>
#include <vector>

#include "zw_pipeline.hpp"
#include "zw_swap_chain.hpp"
#include "zw_window.hpp"
namespace zw {
class FirstApp {
   public:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;
    FirstApp();
    ~FirstApp();
    FirstApp(const FirstApp &) = delete;
    FirstApp &operator=(const FirstApp &) = delete;

    void run();

   private:
    void createPipelineLayout();
    void createPipeline();
    void createCommandBuffers();
    void drawFrame();
    ZWWindow zwWindow{this->WIDTH, this->HEIGHT, "HELLO VULKAN"};
    ZWDevice zwDevice{zwWindow};
    ZWSwapChain zwSwapChain{this->zwDevice, this->zwWindow.getExtent()};
    std::unique_ptr<ZWPipeline> zwPipeline;
    VkPipelineLayout zwPipelineLayout;
    std::vector<VkCommandBuffer> commandBuffers;
    // ZWPipeline zwPipeline{this->zwDevice,
    //                       "../src/shaders/simple_vert.vert.spv",
    //                       "../src/shaders/simple_frag.frag.spv",
    //                       ZWPipeline::defaultPipelineConfigInfo(
    //                           this->WIDTH, this->HEIGHT)};
};
}  // namespace zw