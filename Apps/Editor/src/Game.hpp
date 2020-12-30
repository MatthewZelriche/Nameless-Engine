#pragma once

#include <NLS-Engine/Core/IGameTemplate.hpp>
#include <NLS-Engine/Rendering/WindowManager.hpp>
#include <NLS-Engine/Rendering/Window.hpp>
#include <NLS-Engine/EventSystem/Event.hpp>

class Game : public NLS::Core::IGameTemplate {
public:
    Game();
private:
    void OnCreate() override;
    void OnUpdate() override;

    void Callback(const NLS::EVENT::OnWinFocusChangedEvent &test);
    void Callback1(const NLS::EVENT::OnWinFocusChangedEvent &test);
    void OnKeyPressed(const NLS::EVENT::OnKeyPressedEvent &test);

    std::weak_ptr<NLS::RENDERING::Window> mWindow;
    std::weak_ptr<NLS::RENDERING::Window> mSecondWindow;
};