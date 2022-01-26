#pragma once
#include "zw_device.hpp"
#include <string>
#include <vector>
namespace zw {
    struct PipelineConfigInfo {};
    class ZWPipeline {
    public:
        ZWPipeline(ZWDevice& device, const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo& configInfo);
        ~ZWPipeline() {}
        ZWPipeline(const ZWPipeline&) = delete;
        void operator=(const ZWPipeline&) = delete;
        static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);
    private:
        static std::vector<char> readFile(const std::string& filepath);
        void createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo& configInfo);
        void createShaderModule(const std::vector<char>& code, VkShaderModule& shaderModule);
        ZWDevice& zwDevice;
        VkPipeline graphicsPipeline;
        VkShaderModule vertShaderModule;
        VkShaderModule fragShaderModule;
    };

}