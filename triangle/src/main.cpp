
//@ author = 'Zhiquan Wang'
//@ maintainer = 'Zhiquan Wang'
//@ email = 'wang4490@purdue.edu'
//@ status = 'development'
//@ laboratory = 'vrlab-purdue'
//@ date = '2020/05/01-9:09 PM'
// Copyright (c) 2020 Zhiquan Wang. All rights reserved.
//That way GLFW will include its own definitions and automatically load the Vulkan header with it.
#define GLFW_INCLUDE_VULKAN  // this define is necessary for glfwCreateWindowSurface
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>
// The cstdlib header provides the EXIT_SUCCESS and EXIT_FAILURE macros.
#include <string.h>

#include <cstdlib>
#include <iostream>
#include <optional>
#include <set>
#include <vector>
// #define NDEBUG
#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsQueueFamily;
    std::optional<uint32_t> presentQueueFamily;
    bool isComplete() {
        return this->graphicsQueueFamily.has_value() && this->presentQueueFamily.has_value();
    }
};
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
    const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};

    // There is no global state in Vulkan and all per-application state is stored in a VkInstance object.
    // Creating a VkInstance object initializes the Vulkan library and
    // allows the application to pass information about itself to the implementation.
    VkInstance instance;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkSurfaceKHR surface;
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
        this->createInstance();
        this->createSurface();
        this->pickPhysicalDevice();
        this->createLogicalDevice();
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(this->window)) {
            // The glfwPollEvents function checks if any events are triggered (like keyboard input or mouse movement events),
            // updates the window state, and calls the corresponding functions (which we can register via callback methods).
            glfwPollEvents();
        }
    }

    void cleanup() {
        vkDestroyDevice(device, nullptr);
        vkDestroySurfaceKHR(instance, surface, nullptr);
        vkDestroyInstance(this->instance, nullptr);
        glfwDestroyWindow(this->window);
        glfwTerminate();
    }

    void createInstance() {
        if (enableValidationLayers && !this->checkValidationLayerSupport()) {
            throw std::runtime_error("validation layers requested,but not available");
        }
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
        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = this->validationLayers.data();
        } else {
            createInfo.enabledLayerCount = 0;
        }
        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
        std::cerr << validationLayers.size() << std::endl;

        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance");
        }
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        // Returns up to requested number of global extension properties
        // extensionCount : pPropertyCount is a pointer to an integer related to the number of extension properties available or queried,
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
        std::cout << "available extensions: " << extensionCount << std::endl;
        for (const auto& extension : extensions) {
            std::cout << '\t' << extension.extensionName << '\n';
        }
    }

    bool pickPhysicalDevice() {
        uint32_t deviceCount = 0;
        // Enumerates the physical devices accessible to a Vulkan instance
        vkEnumeratePhysicalDevices(this->instance, &deviceCount, nullptr);
        std::cout << "available device number: " << deviceCount << std::endl;
        if (deviceCount == 0) {
            throw std::runtime_error("failed to find GPUs with Vulkan support!");
        }
        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(this->instance, &deviceCount, devices.data());

        for (auto& device : devices) {
            if (this->isDeviceSuitable(device)) {
                this->physicalDevice = device;
                break;
            }
        }
        if (this->physicalDevice == VK_NULL_HANDLE) {
            throw std::runtime_error("failed to find a suitable GPU!");
        }
        return true;
    }

    bool checkValidationLayerSupport() {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
        for (const char* layerName : validationLayers) {
            bool layerFound = false;
            for (const auto& layerProperties : availableLayers) {
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
    bool isDeviceSuitable(VkPhysicalDevice device) {
        // VkPhysicalDeviceProperties deviceProperties;
        // VkPhysicalDeviceFeatures deviceFeatures;
        // vkGetPhysicalDeviceProperties(device, &deviceProperties);
        // vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
        // std::cout << deviceProperties.deviceName << std::endl;
        // return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU &&
        //        deviceFeatures.geometryShader;
        QueueFamilyIndices indices = findQueueFamilies(device);
        return indices.isComplete();
    }

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {
        QueueFamilyIndices indices;
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
        int i = 0;
        for (auto& queueFamily : queueFamilies) {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.graphicsQueueFamily = i;
            }
            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, this->surface, &presentSupport);
            if (presentSupport) {
                indices.presentQueueFamily = i;
            }
            if (indices.isComplete()) {
                break;
            }
            i++;
        }

        return indices;
    }

    void createLogicalDevice() {
        
        // Specifying the queues to be created
        QueueFamilyIndices indices = this->findQueueFamilies(this->physicalDevice);
        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsQueueFamily.value(), indices.presentQueueFamily.value()};
        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies) {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        // Specifying used device features
        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.queueCreateInfoCount = 1;
        VkPhysicalDeviceFeatures deviceFeatures{};
        createInfo.pEnabledFeatures = &deviceFeatures;
        if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &this->device) != VK_SUCCESS) {
            throw std::runtime_error("failed to create logical device!");
        }
        vkGetDeviceQueue(device, indices.graphicsQueueFamily.value(), 0, &this->graphicsQueue);
        vkGetDeviceQueue(device, indices.presentQueueFamily.value(), 0, &this->presentQueue);
    }
    void createSurface() {
        if (glfwCreateWindowSurface(this->instance, this->window, nullptr, &surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
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