//
//  Utils.cpp
//  Vulkan Renderer
//
//  Created by Jake Jongejans on 15/11/2021.
//

#include "../VKRenderer.hpp"

std::vector<char> VKRenderer::readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("failed to open file!");
    }
    
    // Start at end to get fileSize.
    size_t fileSize = (size_t) file.tellg();
    std::vector<char> buffer(fileSize);
    
    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();

    return buffer;
}
