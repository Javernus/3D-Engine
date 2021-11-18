//
//  UniformBufferObject.hpp
//  Vulkan Renderer
//
//  Created by Jake Jongejans on 18/11/2021.
//

#ifndef UniformBufferObject_hpp
#define UniformBufferObject_hpp

struct UniformBufferObject {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};

#endif /* UniformBufferObject_hpp */
