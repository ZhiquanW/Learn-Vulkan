#include "first_app.hpp"
namespace zw {
FirstApp::FirstApp() {
    this->createPipelineLayout();
    this->createPipeline();
    this->createCommandBuffers();
}
FirstApp::~FirstApp() {
    vkDestroyPipelineLayout(this->zwDevice.device(),
                            this->zwPipelineLayout, nullptr);
}
void FirstApp::run() {
    while (!this->zwWindow.shouldClose()) {
        /* code */
        glfwPollEvents();
    }
}
void FirstApp::createPipelineLayout() {
    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType =
        VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0;
    pipelineLayoutInfo.pSetLayouts = nullptr;
    pipelineLayoutInfo.pushConstantRangeCount = 0;
    pipelineLayoutInfo.pPushConstantRanges = nullptr;
    if (vkCreatePipelineLayout(this->zwDevice.device(),
                               &pipelineLayoutInfo, nullptr,
                               &this->zwPipelineLayout) != VK_SUCCESS) {
        throw std::runtime_error("failed to create pipeline layout");
    }
}

void FirstApp::createPipeline() {
    auto pipelineConfig = ZWPipeline::defaultPipelineConfigInfo(
        this->zwSwapChain.width(), this->zwSwapChain.height());
    pipelineConfig.renderPass = this->zwSwapChain.getRenderPass();
    pipelineConfig.pipelineLayout = this->zwPipelineLayout;
    this->zwPipeline = std::make_unique<ZWPipeline>(
        this->zwDevice, "../src/shaders/simple_vert.vert.spv",
        "../src/shaders/simple_frag.frag.spv", pipelineConfig);
}
void FirstApp::createCommandBuffers() {}
void FirstApp::drawFrame() {}
}  // namespace zw