#pragma once

#include <memory>

#include "NLS-Engine/Core/NLS_API_Export.h"

#include "NLS-Engine/IO/InputManager.hpp"
#include "NLS-Engine/Rendering/WindowManager.hpp"
#include "NLS-Engine/SharpScripting/RuntimeHost.hpp"
#include "NLS-Engine/Core/ProjectManager.hpp"

class NLS_API_EXPORT SubsystemLocator {
private:
    //static SubsystemLocator sLocator;
public:
    //static inline SubsystemLocator& GetLocator() { return sLocator; }
    static RuntimeHost& GetRuntimeHost();
    static ProjectManager& GetProjectManager();
    static NLS::RENDERING::WindowManager& GetWindowManager();
    static NLS::INPUT::InputManager& GetInputManager();
};