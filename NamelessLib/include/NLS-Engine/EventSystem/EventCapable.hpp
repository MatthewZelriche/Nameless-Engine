#pragma once

#include <memory>
#include <functional>
#include <vector>
#include <robin-hood/robin_hood.h>

#include "NLS-Engine/Core/NLS_API_Export.h"
#include "Event.hpp"

namespace NLS::EVENT {
/**
* @brief The central manager class for the Event System. Inherit from this abstract base class to give your class access to the Event System.
* 
* This abstract base class provides functionality for managing event callback listeners and publishing events. Events can be
* either Queued (delayed processing at a fixed point once per frame) or Blocking (processed immediately as the event is published).
* Callback functions are organized based on the EventType they are listening for.
* Classes that inherit from this abstract base class can add or remove callback functions and publish events. 
* @see EventType
*/
class NLS_API_EXPORT EventCapable {
private:
    static robin_hood::unordered_node_map<EventType, std::vector<std::function<void(BaseEvent&)>>> sBlockingCallbacks;
    static robin_hood::unordered_node_map<EventType, std::vector<std::function<void(BaseEvent&)>>> sQueuedCallbacks;
    static std::vector<std::unique_ptr<BaseEvent>> sListOfQueuedEvents;
public:
    virtual ~EventCapable() = 0;
protected:
    EventCapable() = default;
    /**
    * @brief Registers a callback function to listen for events of a specified EventType
    * 
    * @tparam EventChild The type of Event that the function callback should listen for.  
    * @param eventCallback The callback to register. 
    * @param isBlocking Whether the callback should listen for blocking or queued events. Defaults to Queued.
    */
    template <class EventChild>
    typename std::enable_if<std::is_base_of<BaseEvent, EventChild>::value, void>::type
    static RegisterForEvent(std::function<void(const EventChild&)> eventCallback, bool isBlocking = false) {
        // Deduce type of template class through static method of BaseEvent
        auto type = EventChild::eventType;

        // We need to wrap the user's callback event in a lambda function so that the function signature matches the requirements of our flatmap.
        // This lambda then just calls the original function callback with the original parameter type. 
        auto callback = [=](BaseEvent &event) { eventCallback(*static_cast<EventChild*>(std::addressof(event))); };

        if (!isBlocking) {
            if (sQueuedCallbacks.count(type) == 0) {
                sQueuedCallbacks[type] = std::vector<std::function<void(BaseEvent&)>>();
            }
            sQueuedCallbacks[type].emplace_back(callback);
        } else {
            if (sBlockingCallbacks.count(type) == 0) {
                sBlockingCallbacks[type] = std::vector<std::function<void(BaseEvent&)>>();
            }
            sBlockingCallbacks[type].emplace_back(callback);
        }
    }

    /**
    * @brief Searches the list of function callbacks and removes the specified callback from the list if found. 
    * 
    * @tparam EventChild The type of Event that the function callback registered to listen for.
    * @param eventCallback The callback to unregister. 
    * @param isBlocking Whether the callback should listen for blocking or queued events. Defaults to Queued.
    */
    template <class EventChild>
    typename std::enable_if<std::is_base_of<BaseEvent, EventChild>::value, void>::type
    static UnregisterForEvent(std::function<void(const EventChild&)> eventCallback, bool isBlocking = false) {
        // Deduce type of template class through static method of BaseEvent
        auto type = EventChild::eventType;

        // We need to wrap the user's callback event in a lambda function so that the function signature matches the requirements of our flatmap.
        // This lambda then just calls the original function callback with the original parameter type. 
        std::function<void(BaseEvent&)> callback = [=](BaseEvent &event) { eventCallback(*static_cast<EventChild*>(std::addressof(event))); };

        // Had to switch from flat map to node map to ensure stable references, otherwise it was causing crashing on windows.
        if (!isBlocking) {
            for (auto &element : sQueuedCallbacks[type]) {
                if (element.template target<std::function<void(BaseEvent &event)>>() == callback.target<std::function<void(BaseEvent &event)>>()) {
                    // Pop and swap for performance - order of the vector does not matter. 
                    std::swap(element, sQueuedCallbacks[type].back());
                    sQueuedCallbacks[type].pop_back();
                }
            }
        } else {
            for (auto& element : sBlockingCallbacks[type]) {
                if (element.template target<std::function<void(BaseEvent & event)>>() == callback.target<std::function<void(BaseEvent & event)>>()) {
                    // Pop and swap for performance - order of the vector does not matter. 
                    std::swap(element, sBlockingCallbacks[type].back());
                    sBlockingCallbacks[type].pop_back();
                }
            }
        }
    }

    /**
    * @brief Passes a given event to every function callback listening for that EventType and executes those function callbacks. 
    * 
    * @tparam EventChild The type of the published event. 
    * @param event The event to send to the function callbacks. 
    */
    template<class EventChild>
    typename std::enable_if<std::is_base_of<BaseEvent, EventChild>::value, void>::type                             
    static SendBlockingEvent(EventChild &event) { 
        for (auto& storedCallback : sBlockingCallbacks[event.GetEventType()]) {
            storedCallback(event);
        }
    }

    /**
    * @brief Adds an event to a list of queued events that has yet to be processed this frame. Events are added onto the end of the queue.
    * 
    * @tparam EventChild The type of the queued event. 
    * @param event The event to be queued.
    * 
    * @see ProcessEventQueue
    */
    // The event object is passed by value instead of reference because we need to std::move it into the queue to convert it to a pointer,
    // and we don't want to invalidate the original event object the user gave us.
    template<class EventChild>
    typename std::enable_if<std::is_base_of<BaseEvent, EventChild>::value>::type   
    static QueueNewEvent(EventChild event) { 
        sListOfQueuedEvents.emplace_back(std::make_unique<EventChild>(std::move(event)));
    }

    /**
    * @brief Processes queued events that have not yet been processed this frame. 
    * 
    * Not only does this method process events that are generated internally from within NamelessLib, it also
    * processes events that come from external libraries, such as GLFW keyboard events. 
    * Queued events from NamelessLib are processed in the order in which they were pushed to the queue. 
    * After all events submitted this frame have been processed, they are cleared from the list to prepare for the next frame. 
    * 
    * @see QueueNewEvent
    */
    void static ProcessEventQueue();
};
}