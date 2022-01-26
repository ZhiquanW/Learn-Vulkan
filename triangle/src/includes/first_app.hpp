#pragma once

#include "zw_pipeline.hpp"
#include "zw_window.hpp"
namespace zw {
    class FirstApp {
    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;
        void run();

    private:
        ZWWindow zwWindow{ this->WIDTH, this->HEIGHT,
                          "HELLO VULKAN" };
        ZWDevice zwDevice{ zwWindow };
        ZWPipeline zwPipeline{ this->zwDevice,
                              "../src/shaders/simple_vert.vert.spv",
                              "../src/shaders/simple_frag.frag.spv",
                              ZWPipeline::defaultPipelineConfigInfo(this->WIDTH, this->HEIGHT) };
    };
}  // namespace zw