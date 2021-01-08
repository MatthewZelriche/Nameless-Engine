#pragma once

#include "NLS-Engine/Core/IGameTemplate.hpp"

#include <NLS-Engine/Rendering/WindowManager.hpp>
#include <NLS-Engine/Rendering/Window.hpp>

// TODO: Figure this out. It's currently hardcoded for only 1 window.
class DefaultEngine : public NLS::Core::IGameTemplate {
public:
    DefaultEngine();
private:
    void OnCreate() override;
    void OnUpdate() override;

    std::weak_ptr<NLS::RENDERING::Window> mWindow;
};