//
//  SwapChainSupportDetails.hpp
//  Vulkan Renderer
//
//  Created by Jake Jongejans on 18/11/2021.
//

#ifndef SwapChainSupportDetails_hpp
#define SwapChainSupportDetails_hpp

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

#endif /* SwapChainSupportDetails_hpp */
