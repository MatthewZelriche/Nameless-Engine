#include "NLS-Engine/EventSystem/EventCapable.hpp"

#include "NLS-Engine/IO/InputManager.hpp"

#include "Log.hpp"

robin_hood::unordered_node_map<NLS::EVENT::EventType, std::vector<std::function<void(NLS::EVENT::BaseEvent&)>>> NLS::EVENT::EventCapable::sBlockingCallbacks;
robin_hood::unordered_node_map<NLS::EVENT::EventType, std::vector<std::function<void(NLS::EVENT::BaseEvent&)>>> NLS::EVENT::EventCapable::sQueuedCallbacks;
std::vector<std::unique_ptr<NLS::EVENT::BaseEvent>> NLS::EVENT::EventCapable::sListOfQueuedEvents;

// Destructor made pure virtual and then declared - this prevents EventCapable from being instantiated, and can only be derived from. 
NLS::EVENT::EventCapable::~EventCapable() {

}

void NLS::EVENT::EventCapable::ProcessEventQueue() { 
    if (!sListOfQueuedEvents.empty()) {
        for (auto &queuedEvent : sListOfQueuedEvents) {
            for (auto &callback : sQueuedCallbacks.at(queuedEvent->GetEventType())) {
                callback(*queuedEvent.get());
            }
        }
        sListOfQueuedEvents.clear();
    }
    NLS::INPUT::InputManager::FlushKeys();
    glfwPollEvents();
}