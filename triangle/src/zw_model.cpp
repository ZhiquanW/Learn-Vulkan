#include "zw_model.hpp"

#include <cstring>
namespace zw {

ZwModel::ZwModel(ZwDevice& device, const std::vector<Vertex>& vertices) : zwDevice{device} {
    this->createVertexBuffers(vertices);
}
ZwModel::~ZwModel() {
    vkDestroyBuffer(this->zwDevice.device(), vertexBuffer, nullptr);
    vkFreeMemory(this->zwDevice.device(), vertexBufferMemory, nullptr);
}

void ZwModel::createVertexBuffers(const std::vector<Vertex>& vertices) {
    vertexCount = static_cast<uint32_t>(vertices.size());
    assert(vertexCount >= 3 && "vertex count mush be at least 3");
    VkDeviceSize bufferSize = sizeof(vertices[0]) * vertexCount;
    this->zwDevice.createBuffer(bufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                                vertexBuffer, vertexBufferMemory);
    void* data;
    // create a map association between *data(host) and vertex buffer memory (gpu)
    vkMapMemory(this->zwDevice.device(), this->vertexBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, vertices.data(), static_cast<size_t>(bufferSize));
    vkUnmapMemory(this->zwDevice.device(), vertexBufferMemory);
}

void ZwModel::draw(VkCommandBuffer cmdBuffer) {
    vkCmdDraw(cmdBuffer, vertexCount, 1, 0, 0);
}
void ZwModel::bind(VkCommandBuffer cmdBuffer) {
    VkBuffer buffers[] = {this->vertexBuffer};
    VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(cmdBuffer, 0, 1, buffers, offsets);
}
std::vector<VkVertexInputBindingDescription> ZwModel::Vertex::getBindingDescriptions() {
    return {{0, sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX}};
}

std::vector<VkVertexInputAttributeDescription> ZwModel::Vertex::getAttributeDescriptions() {
    return {{0, 0, VK_FORMAT_R32G32_SFLOAT, 0}};
}
}  // namespace zw