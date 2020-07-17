#include "Game.hpp"

#include "Log.hpp"


void Game::Callback(const NLS::EVENT::OnWinFocusChangedEvent &test) {
    NLSLOG::Info("Game", "Win Focus Changed! {}", (void*)test.GetActiveWindow());
}

void Game::Callback1(const NLS::EVENT::OnWinFocusChangedEvent &test) {
    NLSLOG::Info("Game", "Win Focus Changed one!");
}

void Game::OnKeyPressed(const NLS::EVENT::OnKeyPressedEvent &test) {
    NLSLOG::Info("Game", "Key pressed!");
}

Game::Game() {
    mWindow = NLS::RENDERING::WindowManager::ConstructWindow("First Window");
    mSecondWindow = NLS::RENDERING::WindowManager::ConstructWindow("First Window");
    NLS::EVENT::OnWinFocusChangedEvent myEvent(mWindow.lock()->GetGLFWWindowInstance());
    NLS::EVENT::OnKeyPressedEvent eventKey;

    RegisterForEvent<NLS::EVENT::OnWinFocusChangedEvent>(std::bind(&Game::Callback, this, std::placeholders::_1), true);
    RegisterForEvent<NLS::EVENT::OnKeyPressedEvent>(std::bind(&Game::OnKeyPressed, this, std::placeholders::_1), true);

    SendBlockingEvent(eventKey);
    SendBlockingEvent(eventKey);
    //QueueNewEvent(eventKey);
    //QueueNewEvent(eventKey);

    RegisterForEvent<NLS::EVENT::OnWinFocusChangedEvent>(std::bind(&Game::Callback1, this, std::placeholders::_1), true);

    SendBlockingEvent(eventKey);
    SendBlockingEvent(eventKey);
    //QueueNewEvent(eventKey);
    //QueueNewEvent(eventKey);

    UnregisterForEvent<NLS::EVENT::OnKeyPressedEvent>(std::bind(&Game::OnKeyPressed, this, std::placeholders::_1), true);

    SendBlockingEvent(eventKey);
    //QueueNewEvent(eventKey);

    SendBlockingEvent(myEvent);
    //QueueNewEvent(myEvent);

}

void Game::OnUpdate() {
    ProcessEventQueue();
}