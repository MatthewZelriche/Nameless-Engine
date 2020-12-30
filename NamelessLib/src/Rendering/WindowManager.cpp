#include "NLS-Engine/Rendering/WindowManager.hpp"

#include "NLS-Engine/EventSystem/Event.hpp"

#include <Log.hpp>



bool NLS::RENDERING::WindowManager::AllWindowsClosed() {
    // Check every GLFWwindow to see if any of them have recieved the terminate signal.
    for (auto it = sListOfWindows.begin(); it != sListOfWindows.end();) {
        if (glfwWindowShouldClose(it->get()->GetGLFWWindowInstance())) {
            // Erases the window that needs to be closed.
            it = sListOfWindows.erase(it);
        } else {
            // Only increase iterator if we didn't find a valid window to erase, 
            // to avoid invalidating iterator. 
            it++;
        }
    }

    // If no more windows exist, we should send the signal to terminate the program.
    if (sListOfWindows.size() == 0) {
        return true;
    }

    return false;
}

std::weak_ptr<NLS::RENDERING::Window> NLS::RENDERING::WindowManager::ConstructWindow(const char *windowTitle) {
    // Create a new window, add it to the tracking list, and set the Callback function for determining the active window.
    sListOfWindows.emplace_back(new Window(windowTitle));
    glfwSetWindowFocusCallback(sListOfWindows.back()->GetGLFWWindowInstance(), WindowManager::GetActiveWindow);

    return sListOfWindows.back();
}

void NLS::RENDERING::WindowManager::GetActiveWindow(GLFWwindow* window, int focused) {
    NLS::EVENT::OnWinFocusChangedEvent windowFocusChanged(window); 
    if (focused) {
        QueueNewEvent(windowFocusChanged);
    }
}

const std::list<std::shared_ptr<NLS::RENDERING::Window>>& NLS::RENDERING::WindowManager::GetListOfWindows() {
    return sListOfWindows;
}