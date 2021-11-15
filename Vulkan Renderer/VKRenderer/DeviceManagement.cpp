//
//  DeviceManagement.cpp
//  Vulkan Renderer
//
//  Created by Jake Jongejans on 15/11/2021.
//

#include "VKRenderer.hpp"

int VKRenderer::rateDeviceSuitability(VkPhysicalDevice device) {
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    
    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
    
    int score = 1;
    
    // Discrete GPUs have a significant performance advantage
    if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
        score += 10000;
    }
    
    // Maximum possible size of textures affects graphics quality
    score += deviceProperties.limits.maxImageDimension2D;
    
    
    QueueFamilyIndices indices = findQueueFamilies(device);
    if (!indices.isComplete()) {
        return 0;
    }
    
    return score;
}

void VKRenderer::pickPhysicalDevice() {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    
    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }
    
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
    
    // Use an ordered map to automatically sort candidates by increasing score
    std::multimap<int, VkPhysicalDevice> candidates;
    
    for (const auto& device : devices) {
        int score = rateDeviceSuitability(device);
        candidates.insert(std::make_pair(score, device));
    }
    
    // Check if the best candidate is suitable at all
    if (candidates.rbegin()->first > 0) {
        physicalDevice = candidates.rbegin()->second;
        
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(candidates.rbegin()->second, &deviceProperties);
        
        std::cout << "Chosen GPU: " << deviceProperties.deviceName << '\n';
    } else {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}

QueueFamilyIndices VKRenderer::findQueueFamilies(VkPhysicalDevice device) {
    QueueFamilyIndices indices;
    
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
    
    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
    
    int i = 0;
    for (const auto& queueFamily : queueFamilies) {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
        }
        
        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
        
        if (presentSupport) {
            indices.presentFamily = i;
        }
        
        if (indices.isComplete()) {
            break;
        }
        
        i++;
    }
    
    return indices;
}

void VKRenderer::createLogicalDevice() {
    QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
    
    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
    queueCreateInfo.queueCount = 1;
    
    float queuePriority = 1.0f;
    queueCreateInfo.pQueuePriorities = &queuePriority;
    
    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.queueCreateInfoCount = 1;
    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = 0;
    
    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }
    
    if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }
    
    vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
}
