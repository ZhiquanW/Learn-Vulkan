#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <functional>
#include <iostream>
#include <stdexcept>

const int WIDTH = 800;
const int HEIGHT = 600;
class HelloTriangleApplication {
public:
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    GLFWwindow *window;
    VkInstance instance;
    void initWindow() {
        glfwInit();  // not create an OpenGL context
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        // disable resized windows
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        // create a glfw window
        window = glfwCreateWindow(
            WIDTH, HEIGHT, "zhiquan wang", nullptr,
            nullptr);  // params: width, height, title, monitor, opengl related}
    }
    void createInstance() {
        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;  // specify the type
                                                             // of the structure
        appInfo.pApplicationName = "Zhiquan App";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine Zhiquan";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;
        VkInstanceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
    }
    void initVulkan() { createInstance(); }

    void mainLoop() {
        while (!glfwWindowShouldClose(this->window)) {
            // check for events
            glfwPollEvents();
        }
    }

    // when window is closed, clean up resources
    void cleanup() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};

int main() {
    HelloTriangleApplication app;

    try {
        app.run();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}