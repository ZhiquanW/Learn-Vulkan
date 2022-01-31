#pragma once
#define GLM_FORCE_RADIANS
#define GML_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <vector>

#include "zw_device.hpp"
namespace zw {
class ZwModel {
   public:
    struct Vertex {
        glm::vec2 position;
        static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
        static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
    };
    ZwModel(ZwDevice &device, const std::vector<Vertex> &vertices);
    ~ZwModel();
    ZwModel(const ZwModel &) = delete;
    ZwModel &operator=(const ZwModel &) = delete;
    void bind(VkCommandBuffer cmdBuffer);
    void draw(VkCommandBuffer cmdBuffer);

   private:
    void createVertexBuffers(const std::vector<Vertex> &vertices);
    ZwDevice &zwDevice;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    uint32_t vertexCount;
};

}  // namespace zw