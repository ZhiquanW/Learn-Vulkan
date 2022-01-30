#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <string>

namespace zw {
class ZWWindow {
   private:
    GLFWwindow *window;
    const int width;
    const int height;
    std::string windowName;

    void initWindow();

   public:
    ZWWindow(int w, int h, std::string name);
    ZWWindow(const ZWWindow &) = delete;
    ZWWindow &operator=(const ZWWindow &) = delete;
    ~ZWWindow();
    bool shouldClose() { return glfwWindowShouldClose(this->window); }
    void createWindowSurface(VkInstance instance,
                             VkSurfaceKHR *surface);
    VkExtent2D getExtent() {
        return {static_cast<uint32_t>(this->width),
                static_cast<uint32_t>(this->height)};
    }
};

}  // namespace zw
