//
//  Header.h
//  3D Engine
//
//  Created by Jake Jongejans on 13/11/2021.
//

#ifndef Header_h
#define Header_h



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
    
    bool isComplete() {
            return graphicsFamily.has_value();
        }
};

#endif /* Header_h */
