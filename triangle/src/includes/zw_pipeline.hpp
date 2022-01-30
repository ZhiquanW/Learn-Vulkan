#pragma once
#include "zw_device.hpp"
#include <string>
#include <vector>
namespace zw {
    struct PipelineConfigInfo {
        // A viewport basically describes the region of the framebuffer 
        // that the output will be rendered to.
        VkViewport viewport; 
        VkRect2D scissor;
        // VkPipelineViewportStateCreateInfo viewportInfo;
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
        VkPipelineRasterizationStateCreateInfo rasterizationInfo;
        VkPipelineMultisampleStateCreateInfo multisampleInfo;
        VkPipelineColorBlendAttachmentState colorBlendAttachment; // a parameter in colorBlend
        VkPipelineColorBlendStateCreateInfo colorBlendInfo;
        VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
        VkPipelineLayout pipelineLayout = nullptr;
        VkRenderPass renderPass = nullptr;
        uint32_t subpass = 0;

    };
    class ZWPipeline {
    public:
        ZWPipeline(ZWDevice& device, const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo& configInfo);
        ~ZWPipeline();
        ZWPipeline(const ZWPipeline&) = delete;
        void operator=(const ZWPipeline&) = delete;
        static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);
    private:
        static std::vector<char> readFile(const std::string& filepath);
        void createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo& configInfo);
        void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);
        ZWDevice& zwDevice;
        VkPipeline graphicsPipeline;
        VkShaderModule vertShaderModule;
        VkShaderModule fragShaderModule;
    };

}