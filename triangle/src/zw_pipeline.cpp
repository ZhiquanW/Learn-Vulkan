#include "zw_pipeline.hpp"

#include <fstream>
#include <iostream>
namespace zw {
    ZWPipeline::ZWPipeline(ZWDevice& device,
        const std::string& vertFilepath,
        const std::string& fragFilepath,
        const PipelineConfigInfo& configInfo)
        : zwDevice{ device } {
        this->createGraphicsPipeline(vertFilepath, fragFilepath,configInfo);
    }
    std::vector<char> ZWPipeline::readFile(
        const std::string& filename) {
        std::ifstream file{ filename,
                           std::ios::ate | std::ios::binary };
        if (!file.is_open()) {
            throw std::runtime_error("failed to open file: " +
                filename);
        }
        size_t fileSize = (size_t)file.tellg();
        std::vector<char> buffer(fileSize);
        file.seekg(0);
        file.read(buffer.data(), fileSize);
        file.close();
        return buffer;
    }

    void ZWPipeline::createGraphicsPipeline(
        const std::string& vertFilepath,
        const std::string& fragFilepath,
        const PipelineConfigInfo& configInfo) {
        auto vertCode = this->readFile(vertFilepath);
        auto fragCode = this->readFile(fragFilepath);
        std::cout << "Vertex Shader Code Size: " << vertCode.size() << "\n";
        std::cout << "Fragment Shader Code Size: " << fragCode.size() << "\n";
    }
    void ZWPipeline::createShaderModule(
        const std::vector<char>& code,
        VkShaderModule& shaderModule) {
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());
        if (vkCreateShaderModule(zwDevice.device(), &createInfo, nullptr, nullptr) != VK_SUCCESS) {
            throw std::runtime_error("failed to create shader module");
        }
    }

    PipelineConfigInfo ZWPipeline::defaultPipelineConfigInfo(uint32_t width, uint32_t height) {
        PipelineConfigInfo configInfo{};
        return configInfo;
    }
}  // namespace zw