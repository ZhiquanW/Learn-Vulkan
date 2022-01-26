#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>
#include <stdexcept>

namespace zw {
class ZWWindow {
   private:
    GLFWwindow* window;
    const int width;
    const int height;
    std::string windowName;

    void initWindow();

   public:
    ZWWindow(int w, int h, std::string name);
    ZWWindow(const ZWWindow &) = delete;
    ZWWindow & operator=(const ZWWindow &) = delete;
    ~ZWWindow();
    bool shouldClose() {
        return glfwWindowShouldClose(this->window);
    }
    void createWindowSurface(VkInstance instance,VkSurfaceKHR * surface);
};

}  // namespace zw
