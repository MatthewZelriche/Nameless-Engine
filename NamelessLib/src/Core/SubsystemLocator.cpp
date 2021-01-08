#include "NLS-Engine/Core/SubsystemLocator.hpp"


//SubsystemLocator SubsystemLocator::sLocator;

RuntimeHost& SubsystemLocator::GetRuntimeHost() {
    static RuntimeHost sRuntimeHost;
    return sRuntimeHost;
}

ProjectManager& SubsystemLocator::GetProjectManager() {
    static ProjectManager sProjectManager;
    return sProjectManager;
}

NLS::RENDERING::WindowManager& SubsystemLocator::GetWindowManager() {
    static NLS::RENDERING::WindowManager sWindowManager;
    return sWindowManager;
}

NLS::INPUT::InputManager& SubsystemLocator::GetInputManager() {
    static NLS::INPUT::InputManager sInputManager;
    return sInputManager;
}



/*
void Engine::SetWindowManager(std::unique_ptr<NLS::RENDERING::WindowManager> windowManager) {
    mWindowManager = std::move(windowManager);
}

void Engine::SetInputManager(std::unique_ptr<NLS::INPUT::InputManager> inputManager) {
    mInputManager = std::move(inputManager);
}
*/

