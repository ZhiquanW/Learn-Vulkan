
//@ author = 'Zhiquan Wang'
//@ maintainer = 'Zhiquan Wang'
//@ email = 'wang4490@purdue.edu'
//@ status = 'development'
//@ laboratory = 'vrlab-purdue'
//@ date = '2020/05/01-9:09 PM'
// Copyright (c) 2020 Zhiquan Wang. All rights reserved.

//That way GLFW will include its own definitions and automatically load the Vulkan header with it.
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

// The cstdlib header provides the EXIT_SUCCESS and EXIT_FAILURE macros.
#include <cstdlib>
#include <iostream>

class HelloTrigneleApplication {
   public:
    void run() {
        this->initWindow();
        this->initVulkan();
        this->mainLoop();
        this->cleanup();
    }

   private:
    GLFWwindow* window;
    const uint32_t win_width = 800;
    const uint32_t win_height = 800;
    void initWindow() {
        // initializes the GLFW library
        glfwInit();
        /*
        Vulkan does not have a context and the Vulkan instance is created via the Vulkan API itself. 
        If you will be using Vulkan to render to a window, disable context creation by setting the GLFW_CLIENT_API hint to GLFW_NO_API.
        */
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        // disable window resizeable
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        // create a actual window
        this->window = glfwCreateWindow(win_height, win_width, "vulkan_main", nullptr, nullptr);
    }
    void initVulkan() {
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(this->window)) {
            // The glfwPollEvents function checks if any events are triggered (like keyboard input or mouse movement events),
            // updates the window state, and calls the corresponding functions (which we can register via callback methods). 
            glfwPollEvents();
        }
    }

    void cleanup() {
        glfwDestroyWindow(this->window);
        glfwTerminate();
    }
};

int main() {
    HelloTrigneleApplication app;
    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_FAILURE;
}