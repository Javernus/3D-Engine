//
//  QueueFamilyIndices.hpp
//  Vulkan Renderer
//
//  Created by Jake Jongejans on 18/11/2021.
//

#ifndef QueueFamilyIndices_hpp
#define QueueFamilyIndices_hpp

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;
    
    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

#endif /* QueueFamilyIndices_hpp */
