#pragma once

#include <memory>
#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>

#include "NLS-Engine/Core/NLS_API_Export.h"

namespace NLS::RENDERING {

// Forward declaration to ensure WindowManager is the only class that can construct a Window.
class WindowManager;

/**
* @brief Wrapper class that encapsulates a GLFWwindow.
*  
* The constructor for this class is private, to ensure that only WindowManager can construct a new Window.
* This is necessary to ensure WindowManager can appropriate track the number of currently alive Windows.
* 
* @see WindowManager
*/
class NLS_API_EXPORT Window {
public:
    /// Returns an instance to the GLFWwindow pointer object. For when you need to communicate with GLFW and it only accepts GLFWwindow*
    inline GLFWwindow* GetGLFWWindowInstance() const { return m_glfwWindowInstance.get(); }
    
    friend WindowManager;
private:
    // TODO: In the future, have Window accept a custom struct of initialization data. 
    Window(const char *windowTitle);
    /// Needed to make GLFWwindow work with smart pointers. 
    struct GLFWDeleterWrapper {
        void operator()(GLFWwindow *window) {
            // Check to make sure the window hasn't already been deleted.
            if (window) {
                glfwDestroyWindow(window); 
            }
        }
    };
    std::unique_ptr<GLFWwindow, GLFWDeleterWrapper> m_glfwWindowInstance { nullptr };
};

}