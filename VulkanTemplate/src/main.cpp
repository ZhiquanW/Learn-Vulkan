
//@ author = 'Zhiquan Wang'
//@ maintainer = 'Zhiquan Wang'
//@ email = 'wang4490@purdue.edu'
//@ status = 'development'
//@ laboratory = 'vrlab-purdue'
//@ date = '2020/05/01-9:09 PM'
// Copyright (c) 2020 Zhiquan Wang. All rights reserved.


#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <cstring>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

const std::vector<const char *> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

bool checkValidatinoLayerSupport() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
    for (const char *layerName : validationLayers) {
        bool layerFound = false;
        std::cout << layerName << std::endl;
        for (const auto &layerProperties : availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) {
            return false;
        }
    }
    return true;
}

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
    VkInstance instance;  //An instance is created by describing your application and any API extensions you will be using.

    void initWindow() {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    }

    void initVulkan() {
        createInstance();
        std::cout << "#1 init vulkan" << std::endl;
    }

    void createInstance() {
//        VkApplicationInfo appInfo = {};
//        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
//        appInfo.pApplicationName = "Hello Triangle";
//        appInfo.applicationVersion = VK_MAKE_VERSION(1,0,0);
//        appInfo.pEngineName = "No Engine";
//        appInfo.engineVersion = VK_MAKE_VERSION(1,0,0);
//        appInfo.apiVersion = VK_API_VERSION_1_0;
        if (enableValidationLayers && !checkValidatinoLayerSupport()) {
            throw std::runtime_error("validation layers requested, but not available!");
        }
        struct VkApplicationInfo appInfo = {
                .sType =  VK_STRUCTURE_TYPE_APPLICATION_INFO,
                .pNext = nullptr,
                .pApplicationName =  "Hello Triangle",
                .applicationVersion =  VK_MAKE_VERSION(1, 0, 0),
                .pEngineName =  "No Engine",
                .engineVersion =  VK_MAKE_VERSION(1, 0, 0),
                .apiVersion =  VK_API_VERSION_1_0
        };

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        auto extensions = getRequiredExtensions();
        createInfo.enabledExtensionCount = extensions.size();
        createInfo.ppEnabledExtensionNames = extensions.data();
        if(enableValidationLayers){
            createInfo.enabledLayerCount = static_cast<uint32_t > (validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        }else{
            createInfo.enabledLayerCount = 0;
        }
        VkResult result = vkCreateInstance(&createInfo, nullptr, &this->instance);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to create a instance");
        } else {
            std::cout << "instance created successfully" << std::endl;
        }
//        uint32_t extensionCount = 0;
//        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
//        std::vector<VkExtensionProperties> extensionProperties(extensionCount);
//        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensionProperties.data());
//        std::cout << "available extensions: \n";
//        for (const auto &extension : extensionProperties) {
//            std::cout << '\t' << extension.extensionName << '\n';
//        }
//        std::cout << "glfw required extensions " << createInfo.enabledExtensionCount << std::endl;
//        for (int i = 0; i < createInfo.enabledExtensionCount; ++i) {
//            std::cout << '\t' << createInfo.ppEnabledExtensionNames[i] << '\n';
//
//        }


    }
    std::vector<const char*> getRequiredExtensions() {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount); //glfw built-in function
        std::cout <<"A " << std::endl;
        std::cout << glfwExtensions << std::endl;
        std::cout << glfwExtensions << std::endl;
        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if (enableValidationLayers) {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        return extensions;
    }
    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanup() {
        vkDestroyInstance(this->instance, nullptr);
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