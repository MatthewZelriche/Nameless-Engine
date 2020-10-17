#include "NLS-Engine/Rendering/GLContext.hpp"

#include <Log.hpp>
#include <GLFW/glfw3.h>


NLS::RENDERING::GLContext::GLContext() {
    if (!glfwInit()) {
        NLSLOG::Error("Engine", "Could not initialize GLFW! Shutting down...");
        std::exit(1);
    }

    // Enable 4.3 profile for debugging if we are in debug mode.
    // Disable for release for wider range of compatibility.
#ifdef NDEBUG
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#elif !NDEBUG
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#endif
}