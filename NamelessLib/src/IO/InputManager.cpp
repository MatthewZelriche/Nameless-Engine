#include "NLS-Engine/IO/InputManager.hpp"

#include "Log.hpp"

GLFWwindow                      *NLS::INPUT::InputManager::sActiveWindow =                  nullptr;
std::array<bool, NLS_MAX_KEYS>  NLS::INPUT::InputManager::sKeyStatesSysDelay =              { false };
std::array<bool, NLS_MAX_KEYS>  NLS::INPUT::InputManager::sKeyStatesBinary =                { false };
char                            NLS::INPUT::InputManager::sNewState =                       0;
std::unique_ptr<NLS::INPUT::KeyBindingSet>  NLS::INPUT::InputManager::sLoadedKeyBindings =  nullptr;  


void NLS::INPUT::InputManager::LoadActiveKeybindingSet(KeyBindingSet &&keybinding) {
    sLoadedKeyBindings = std::make_unique<KeyBindingSet>(keybinding);
}

bool NLS::INPUT::InputManager::GetKeyDown(const std::string &bindingName) {
    return sKeyStatesBinary[static_cast<int>(sLoadedKeyBindings->GetActionKeybind(bindingName))];
}

bool NLS::INPUT::InputManager::GetKeyDown(const std::string &bindingName, GLFWwindow *specificWindow) {
    if (sActiveWindow == specificWindow) {
        return sKeyStatesBinary[static_cast<int>(sLoadedKeyBindings->GetActionKeybind(bindingName))];
    }
    return false; 
}

bool NLS::INPUT::InputManager::GetKeyDownSysDelay(const std::string &bindingName) {
    return sKeyStatesSysDelay[static_cast<int>(sLoadedKeyBindings->GetActionKeybind(bindingName))];
}

bool NLS::INPUT::InputManager::GetKeyDownSysDelay(const std::string &bindingName, GLFWwindow *specificWindow) {
    if (sActiveWindow == specificWindow) {
        return sKeyStatesSysDelay[static_cast<int>(sLoadedKeyBindings->GetActionKeybind(bindingName))];
    }
    return false; 
}

void NLS::INPUT::InputManager::FlushKeys() {
    // This ensures that that during the first frame, the callback function is registered with the event system.
    // Kind of an ugly way of doing this but I can't think of anything better at the moment. 
    static bool initialized = false;
    if (initialized == false) {
        RegisterForEvent<EVENT::OnWinFocusChangedEvent>(&InputManager::GetWindowFocus);
        initialized = true;
    }

    sKeyStatesSysDelay.fill(false);
}


void NLS::INPUT::InputManager::GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        sKeyStatesBinary[key] = true;
        sKeyStatesSysDelay[key] = true;
        sNewState = GLFW_PRESS;
    } else if (action == GLFW_RELEASE) {
        sKeyStatesBinary[key] = false;
        sKeyStatesSysDelay[key] = false;
        sNewState = GLFW_RELEASE;
    } else if (action == GLFW_REPEAT) {                             
        sKeyStatesSysDelay[key] = true;
        sNewState = GLFW_REPEAT;
    }
}

void NLS::INPUT::InputManager::GetWindowFocus(const EVENT::OnWinFocusChangedEvent& event) {
    sActiveWindow = event.GetActiveWindow();
    // Set the Key Callback function to the currently active window. 
    if (sActiveWindow) { 
        glfwSetKeyCallback(sActiveWindow, GLFWKeyCallback);
    }
}