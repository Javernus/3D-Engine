//
//  FragmentShader.cpp
//  Vulkan Renderer
//
//  Created by Jake Jongejans on 15/11/2021.
//

#version 450

layout(location = 0) in vec3 fragColor;

layout(location = 0) out vec4 outColor;

void main() {
    outColor = vec4(fragColor, 1.0);
}
