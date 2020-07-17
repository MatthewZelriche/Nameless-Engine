#include "NLS-Engine/Core/IGameTemplate.hpp"

#include <Log.hpp>

#include "NLS-Engine/Rendering/WindowManager.hpp"

void NLS::Core::IGameTemplate::Run() {
    NLSLOG::Info("Engine", "Running game...");
    InternalUpdate();
}


void NLS::Core::IGameTemplate::InternalUpdate() {
    // TODO: loop here.
    // Presumably, InternalUpdate() is also where we would loop through all
    // of our Systems for our ECS. But what about Entities that utilize FixedUpdate?
    while (!NLS::RENDERING::WindowManager::AllWindowsClosed()) {
        OnUpdate();
    }
}