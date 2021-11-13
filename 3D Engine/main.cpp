//
//  main.cpp
//  3D Engine
//
//  Created by Jake Jongejans on 13/11/2021.
//

#include "core.h"

class HelloTriangleApplication {
  
public:
  void run() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
  }
  
private:
  const uint32_t WIDTH = 800;
  const uint32_t HEIGHT = 600;
  const char** glfwExtensions;
  
  uint32_t glfwExtensionCount = 0;
  
  GLFWwindow* window;
  VkInstance instance;
  
  void initWindow() {
    glfwInit();
    
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
  }
  
  void initVulkan() {
    createInstance();
  }
  
  void createInstance() {
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;
    
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    
    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;
    
    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
    
    if (result != VK_SUCCESS) {
      printf("The error: %i\n", result);
      throw std::runtime_error("failed to create instance!");
    }
    
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    
    std::vector<VkExtensionProperties> extensions(extensionCount);
    
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
    
    int missingExtention = 0;
    
    for (const auto& extension : extensions) {
      if (std::find(glfwExtensions, glfwExtensions + extensionCount, extension.extensionName) != glfwExtensions + extensionCount) {
        std::cout << '\t' << extension.extensionName << '\n';
        missingExtention = 1;
      }
    }
    
    if (missingExtention) std::cout << "The above mentioned extensions are missing.\n";
  }
  
  void mainLoop() {
    while (!glfwWindowShouldClose(window)) {
      glfwPollEvents();
    }
  }
  
  void cleanup() {
    vkDestroyInstance(instance, nullptr);
    glfwDestroyWindow(window);
    glfwTerminate();
  }
};

int main() {
  HelloTriangleApplication app;
  
  try {
    app.run();
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}
