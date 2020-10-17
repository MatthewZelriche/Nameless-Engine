#include "NLS-Engine/Rendering/Window.hpp"

#include <Log.hpp>

#include <glad/glad.h>

NLS::RENDERING::Window::Window(const char *windowTitle) {
    NLSLOG::Info("Engine", "--- Constructing a new window of name '{}'... ---", windowTitle);

    // We create a new GLFW window that our wrapper will be handling. 
    m_glfwWindowInstance.reset(glfwCreateWindow(1024, 768, "test", nullptr, nullptr));
    if (!m_glfwWindowInstance) {
        throw std::runtime_error("GLFW Failed to successfully create a window instance.");
    }

    
    // We set this window's context to be current so that we can load OpenGL functions into
    // The context responsible for it
    glfwMakeContextCurrent(m_glfwWindowInstance.get());

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        NLSLOG::Error("Engine", "Could not retrieve OpenGL Function Pointers! Shutting down...");
        std::exit(1);
    }   

    glViewport(0, 0, 1024,768);
    glfwSetFramebufferSizeCallback(m_glfwWindowInstance.get(), Window::framebuffer_size_callback);

    NLSLOG::Info("Engine", "--- New Window has succesfully been created! ---");
}

void NLS::RENDERING::Window::Render() const {
    glfwMakeContextCurrent(m_glfwWindowInstance.get());
    glfwSwapBuffers(m_glfwWindowInstance.get());
}


void NLS::RENDERING::Window::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}