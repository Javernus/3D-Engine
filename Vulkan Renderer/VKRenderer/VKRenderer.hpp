//
//  VKRenderer.hpp
//  Vulkan Renderer
//
//  Created by Jake Jongejans on 15/11/2021.
//

#ifndef VKRenderer_hpp
#define VKRenderer_hpp

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <map>
#include <optional>

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;
    
    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

class VKRenderer {
    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;
    const char** glfwExtensions;

    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

    #ifdef DEBUG
    const bool enableValidationLayers = true;
    #else
    const bool enableValidationLayers = false;
    #endif

    uint32_t glfwExtensionCount = 0;

    GLFWwindow* window;
    
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkPhysicalDeviceFeatures deviceFeatures{};
    VkDevice device;
    VkQueue graphicsQueue;
    VkSurfaceKHR surface;
    
    
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
                                                        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                        VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                                        void* pUserData);
    
public:
    void run();
private:
    void initWindow();
    void initVulkan();
    void createSurface();
    int rateDeviceSuitability(VkPhysicalDevice device);
    void pickPhysicalDevice();
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    void createLogicalDevice();
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    void setupDebugMessenger();
    std::vector<const char*> getRequiredExtensions();
    bool checkValidationLayerSupport();
    void createInstance();
    void mainLoop();
    void cleanup();
};

#endif /* VKRenderer_hpp */
