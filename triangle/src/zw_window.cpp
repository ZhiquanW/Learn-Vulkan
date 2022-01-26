#include "zw_window.hpp"
namespace zw {
ZWWindow::ZWWindow(int w, int h, std::string name) : width{w}, height{h}, windowName{name} {
    this->initWindow();
}
ZWWindow::~ZWWindow() {
    glfwDestroyWindow(this->window);
    glfwTerminate();
}
void ZWWindow::initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    this->window = glfwCreateWindow(this->width, this->height, this->windowName.c_str(), nullptr, nullptr);
}

void ZWWindow::createWindowSurface(VkInstance instance,VkSurfaceKHR * surface){
    if(glfwCreateWindowSurface(instance,window,nullptr,surface) != VK_SUCCESS){
         throw std::runtime_error("failed to create window surface");
    }

}

}  // namespace zw
