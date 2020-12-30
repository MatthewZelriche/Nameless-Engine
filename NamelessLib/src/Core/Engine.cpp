#include "NLS-Engine/Core/Engine.hpp"

#include "NLS-Engine/SharpScripting/RuntimeHost.hpp"
#include "NLS-Engine/IO/InputManager.hpp"
#include "NLS-Engine/Rendering/WindowManager.hpp"
#include "NLS-Engine/IO/InputManager.hpp"


std::unique_ptr<Engine> Engine::mEngine = std::make_unique<Engine>();


void Engine::SetRuntimeHost(std::unique_ptr<RuntimeHost> runtimeHost) {
    mRuntimeHost = std::move(runtimeHost);
}

void Engine::SetWindowManager(std::unique_ptr<NLS::RENDERING::WindowManager> windowManager) {
    mWindowManager = std::move(windowManager);
}

void Engine::SetInputManager(std::unique_ptr<NLS::INPUT::InputManager> inputManager) {
    mInputManager = std::move(inputManager);
}

