#pragma once

#include <memory>
#include <vector>

#include "zw_model.hpp"
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
    void loadModels();
    void createPipelineLayout();
    void createPipeline();
    void createCommandBuffers();
    void drawFrame();
    ZwWindow zwWindow{this->WIDTH, this->HEIGHT, "HELLO VULKAN"};
    ZwDevice zwDevice{zwWindow};
    ZwSwapChain zwSwapChain{this->zwDevice, this->zwWindow.getExtent()};
    std::unique_ptr<ZwPipeline> zwPipeline;
    VkPipelineLayout zwPipelineLayout;
    std::vector<VkCommandBuffer> commandBuffers;
    std::unique_ptr<ZwModel> zwModel;
    // ZwPipeline zwPipeline{this->zwDevice,
    //                       "../src/shaders/simple_vert.vert.spv",
    //                       "../src/shaders/simple_frag.frag.spv",
    //                       ZwPipeline::defaultPipelineConfigInfo(
    //                           this->WIDTH, this->HEIGHT)};
};
}  // namespace zw