#pragma once

#include <memory>

#include "NLS-Engine/Core/NLS_API_Export.h"
#include "NLS-Engine/IO/KeyBindingSet.hpp"
#include "NLS-Engine/EventSystem/EventCapable.hpp"
#include "NLS-Engine/EventSystem/Event.hpp"
#include "NLS-Engine/IO/KeyCodes.hpp"

namespace NLS::INPUT {

class NLS_API_EXPORT InputManager : EVENT::EventCapable {
public:
    /// Load the desired Keybinding Set.
    static void LoadActiveKeybindingSet(KeyBindingSet &&keybinding);
    /// Gets the state of any key in a binary on/off fashion.
    static bool GetKeyDown(const std::string &bindingName);
    /// Gets the state of any key in a binary on/off fashion, listening only on a specific window.
    static bool GetKeyDown(const std::string &bindingName, GLFWwindow *specificWindow);
    /// Gets the state of any key, including delay introduced by the OS. 
    static bool GetKeyDownSysDelay(const std::string &bindingName);
    /// Gets the state of any key, including delay introduced by the OS. , listening only on a specific window.
    static bool GetKeyDownSysDelay(const std::string &bindingName, GLFWwindow *specificWindow);
    /// For GetKeyStateSysDelay() to work, we must set the state of every key to false at the end of every frame. 
    static void FlushKeys();
private:
    /// Callback Function utilized by GLFW to recieve input from the OS. 
    static void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    /// Function utilized by the NLS Event System to check which Window is focused, so that Input can be spolled on specific windows only. 
    static void GetWindowFocus(const EVENT::OnWinFocusChangedEvent& event);

    static std::array<bool, NLS_MAX_KEYS> sKeyStatesSysDelay;
    static std::array<bool, NLS_MAX_KEYS> sKeyStatesBinary; 
    static GLFWwindow* sActiveWindow;
    static char sNewState;  
    static std::unique_ptr<KeyBindingSet> sLoadedKeyBindings; 
};
}