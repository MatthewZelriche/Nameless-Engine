#include "NLS-Engine/Core/IGameTemplate.hpp"

#include <Log.hpp>

#include "NLS-Engine/Rendering/WindowManager.hpp"
#include "NLS-Engine/IO/InputManager.hpp"

#include "NLS-Engine/Core/SubsystemLocator.hpp"

void NLS::Core::IGameTemplate::Run() {
    NLSLOG::Info("Engine", "Creating Subsystems...");
    // Specific startup order goes here. 
    SubsystemLocator::GetProjectManager();
    SubsystemLocator::GetRuntimeHost();
    SubsystemLocator::GetWindowManager();
    SubsystemLocator::GetInputManager();
    NLSLOG::Info("Engine", "Running game...");
    OnCreate();
    InternalUpdate();
}

void NLS::Core::IGameTemplate::InternalUpdate() {
    // TODO: loop here.
    // Presumably, InternalUpdate() is also where we would loop through all
    // of our Systems for our ECS. But what about Entities that utilize FixedUpdate?
   while (!SubsystemLocator::GetWindowManager().AllWindowsClosed()) {
       OnUpdate();

       for (auto &element : SubsystemLocator::GetWindowManager().GetListOfWindows()) {
           element->Render();
       }
   }
}