//
//  main.cpp
//  Vulkan Renderer
//
//  Created by Jake Jongejans on 13/11/2021.
//

#include "main.hpp"
#include "VKRenderer/VKRenderer.hpp"

int main() {
	VKRenderer app;
	
	try {
		app.run();
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}
