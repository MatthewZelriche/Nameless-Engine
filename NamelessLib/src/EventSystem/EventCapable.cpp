#include "NLS-Engine/EventSystem/EventCapable.hpp"

robin_hood::unordered_flat_map<NLS::EVENT::EventType, std::vector<std::function<void(NLS::EVENT::BaseEvent&)>>> NLS::EVENT::EventCapable::sBlockingCallbacks;
robin_hood::unordered_flat_map<NLS::EVENT::EventType, std::vector<std::function<void(NLS::EVENT::BaseEvent&)>>> NLS::EVENT::EventCapable::sQueuedCallbacks;
std::vector<NLS::EVENT::BaseEvent> NLS::EVENT::EventCapable::sListOfQueuedEvents;

// Destructor made pure virtual and then declared - this prevents EventCapable from being instantiated, and can only be derived from. 
NLS::EVENT::EventCapable::~EventCapable() {

}