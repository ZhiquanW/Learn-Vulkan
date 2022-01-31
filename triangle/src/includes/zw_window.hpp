#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <string>

namespace zw {
class ZwWindow {
   private:
    GLFWwindow *window;
    const int width;
    const int height;
    std::string windowName;

    void initWindow();

   public:
    ZwWindow(int w, int h, std::string name);
    ZwWindow(const ZwWindow &) = delete;
    ZwWindow &operator=(const ZwWindow &) = delete;
    ~ZwWindow();
    bool shouldClose() { return glfwWindowShouldClose(this->window); }
    void createWindowSurface(VkInstance instance,
                             VkSurfaceKHR *surface);
    VkExtent2D getExtent() {
        return {static_cast<uint32_t>(this->width),
                static_cast<uint32_t>(this->height)};
    }
};

}  // namespace zw
