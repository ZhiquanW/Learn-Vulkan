
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
#include <vector>

class HelloTrigneleApplication {
   public:
    void run() {
        this->initWindow();
        this->initVulkan();
        // this->mainLoop();
        this->cleanup();
    }

   private:
    GLFWwindow* window;
    const uint32_t win_width = 800;
    const uint32_t win_height = 800;
    // There is no global state in Vulkan and all per-application state is stored in a VkInstance object.
    // Creating a VkInstance object initializes the Vulkan library and
    // allows the application to pass information about itself to the implementation.
    VkInstance instance;
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
        createInstance();
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(this->window)) {
            // The glfwPollEvents function checks if any events are triggered (like keyboard input or mouse movement events),
            // updates the window state, and calls the corresponding functions (which we can register via callback methods).
            glfwPollEvents();
        }
    }

    void cleanup() {
        vkDestroyInstance(this->instance, nullptr);
        glfwDestroyWindow(this->window);
        glfwTerminate();
    }

    void createInstance() {
        //initialize the Vulkan library by creating an instance
        VkApplicationInfo appInfo{};
        //many structs in Vulkan require you to explicitly specify the type in the sType member.
        // Vulkan is C API, that can not set default value in structure
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        /*
        pApplicationName, applicationVersion, pEngineName, engineVersion - 
        These are free-form fields that the application may provide if desired. 
        Some implementations of tools, loaders, layers, or drivers 
        may use these fields to provide information while debugging or collecting information for reports, etc.
        It may even be possible for drivers to change their behaviors depending on the application that is running.
        */
        appInfo.pApplicationName = "Hello Triangle";  // is NULL or is a pointer to a null-terminated UTF-8 string containing the name of the application.
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        /*
        pApplicationInfo is NULL or a pointer to a VkApplicationInfo structure.
        If not NULL, this information helps implementations recognize behavior inherent to classes of applications.
        VkApplicationInfo is defined in detail above.
        */
        createInfo.pApplicationInfo = &appInfo;
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        /*
        This function returns an array of names of Vulkan instance extensions required by GLFW 
        for creating Vulkan surfaces for GLFW windows.
        If successful, the list will always contain VK_KHR_surface, 
        so if you don't require any additional extensions you can pass this list directly to the VkInstanceCreateInfo struct.
        */
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);  //glfw api
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        createInfo.enabledLayerCount = 0;
        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance");
        }
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        std::cout << extensionCount << std::endl;
        // Returns up to requested number of global extension properties
        // extensionCount : pPropertyCount is a pointer to an integer related to the number of extension properties available or queried,
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
        std::cout << "available extensions:\n";
        for (const auto& extension : extensions) {
            std::cout << '\t' << extension.extensionName << '\n';
        }
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