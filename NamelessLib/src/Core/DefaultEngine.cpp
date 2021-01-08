#include "NLS-Engine/Core/DefaultEngine.hpp"
#include "NLS-Engine/Core/SubsystemLocator.hpp"


DefaultEngine::DefaultEngine() {

}

void DefaultEngine::OnCreate() {
    mWindow = SubsystemLocator::GetWindowManager().ConstructWindow("Engine Placeholder");
}

void DefaultEngine::OnUpdate() {
    ProcessEventQueue();
}