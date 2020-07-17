#include "NLS-Engine/Rendering/Window.hpp"

#include <Log.hpp>


NLS::RENDERING::Window::Window(const char *windowTitle) {
    NLSLOG::Info("Engine", "--- Constructing a new window of name '{}'... ---", windowTitle);
    
    // Initialize GLFW if this is the first window we are creating.
    // If more than one windows are active, glfwInit will simply immediately return true.
    if (!glfwInit()) {
        throw std::runtime_error("GLFW Failed to Initialize, cannot construct window.");
    }

    if (!glfwVulkanSupported()) {
        throw std::runtime_error("Vulkan loader was not found.");
    }


    // We create a new GLFW window that our wrapper will be handling. 
    m_glfwWindowInstance.reset(glfwCreateWindow(1024, 768, "test", nullptr, nullptr));
    if (!m_glfwWindowInstance) {
        throw std::runtime_error("GLFW Failed to successfully create a window instance.");
    }

    
    // We set this window's context to be current so that we can load OpenGL functions into
    // The context responsible for it
    glfwMakeContextCurrent(m_glfwWindowInstance.get());

    //is this the right way to do things? This is mostly boilerplate code to get windows up until I learn more about Vulkan.
    PFN_vkCreateInstance pfnCreateInstance = (PFN_vkCreateInstance)glfwGetInstanceProcAddress(NULL, "vkCreateInstance");


    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    NLSLOG::Info("Engine", "Extensions supported: {}", extensionCount);
    NLSLOG::Info("Engine", "--- New Window has succesfully been created! ---");
}