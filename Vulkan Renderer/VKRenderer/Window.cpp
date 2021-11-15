//
//  Window.cpp
//  Vulkan Renderer
//
//  Created by Jake Jongejans on 15/11/2021.
//

#include "VKRenderer.hpp"

void VKRenderer::createSurface() {
    if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface!");
    }
}
