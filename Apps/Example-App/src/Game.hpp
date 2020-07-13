#pragma once

#include <NLS-Engine/Core/IGameTemplate.hpp>
#include <NLS-Engine/EventSystem/Event.hpp>

class Game : public NLS::Core::IGameTemplate {
private:
    void OnUpdate() override;

    void Callback(const NLS::EVENT::OnWinFocusChangedEvent &test);
    void Callback1(const NLS::EVENT::OnWinFocusChangedEvent &test);
    void OnKeyPressed(const NLS::EVENT::OnKeyPressedEvent &test);
};