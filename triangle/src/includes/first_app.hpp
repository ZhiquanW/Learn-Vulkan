#pragma once

#include "zw_window.hpp"
#include "zw_pipeline.hpp"
namespace zw {
class FirstApp {
   public:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;
    void run();
   
   private:
    ZWWindow zwWindow{this->WIDTH, this->HEIGHT, "HELLO VULKAN"};
    ZWPipeline zwPipeline{"../src/shaders/simple_vert.vert.spv","../src/shaders/simple_frag.frag.spv"};
};
}  // namespace zw