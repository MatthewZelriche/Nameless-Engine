#pragma once

#include <memory>

#include "NLS-Engine/Core/NLS_API_Export.h"

#include "NLS-Engine/IO/InputManager.hpp"
#include "NLS-Engine/Rendering/WindowManager.hpp"
#include "NLS-Engine/SharpScripting/RuntimeHost.hpp"

class NLS_API_EXPORT Engine {
private:
    static std::unique_ptr<Engine> mEngine;

    std::unique_ptr<RuntimeHost> mRuntimeHost;
    std::unique_ptr<NLS::RENDERING::WindowManager> mWindowManager;
    std::unique_ptr<NLS::INPUT::InputManager> mInputManager;
public:
    static inline Engine& GetEngine() { return *mEngine.get(); }
    inline RuntimeHost& GetRuntimeHost() const { return *mRuntimeHost.get(); }
    inline NLS::RENDERING::WindowManager& GetWindowManager() const { return *mWindowManager.get(); }
    inline NLS::INPUT::InputManager& GetInputManager() const { return *mInputManager.get(); }

    void SetRuntimeHost(std::unique_ptr<RuntimeHost> runtimeHost);
    void SetWindowManager(std::unique_ptr<NLS::RENDERING::WindowManager> windowManager);
    void SetInputManager(std::unique_ptr<NLS::INPUT::InputManager> inputManager);
};