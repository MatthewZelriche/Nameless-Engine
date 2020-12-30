#include "NLS-Engine/Core/IGameTemplate.hpp"

#include <Log.hpp>

#include "NLS-Engine/Rendering/WindowManager.hpp"
#include "NLS-Engine/IO/InputManager.hpp"

#include "NLS-Engine/Core/Engine.hpp"

void NLS::Core::IGameTemplate::Run() {
    Engine::GetEngine();
    Engine::GetEngine().SetRuntimeHost(std::make_unique<RuntimeHost>());
    Engine::GetEngine().SetWindowManager(std::make_unique<NLS::RENDERING::WindowManager>());
    Engine::GetEngine().SetInputManager(std::make_unique<NLS::INPUT::InputManager>());
    NLSLOG::Info("Engine", "Running game...");
    OnCreate();
    InternalUpdate();
}

void NLS::Core::IGameTemplate::InternalUpdate() {
    // TODO: loop here.
    // Presumably, InternalUpdate() is also where we would loop through all
    // of our Systems for our ECS. But what about Entities that utilize FixedUpdate?
   while (!Engine::GetEngine().GetWindowManager().AllWindowsClosed()) {
       OnUpdate();

       for (auto &element : Engine::GetEngine().GetWindowManager().GetListOfWindows()) {
           element->Render();
       }
   }
}