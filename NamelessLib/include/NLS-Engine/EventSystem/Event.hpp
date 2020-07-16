#pragma once

#include <GLFW/glfw3.h>

#include "NLS-Engine/Core/NLS_API_Export.h"

namespace NLS::EVENT {
/// EventType holds all the different possible types an Event can be. Empty should normally never be used, except for BaseEvent. 
enum class NLS_API_EXPORT EventType {
    OnKeyPressed, OnKeyReleased, OnWinFocusChanged, Empty
};

/// The BaseEvent Class that all Events must derive from in order to be a valid event type.
class NLS_API_EXPORT BaseEvent {
private:
    EventType mType { EventType::Empty };
public:
    BaseEvent() = delete;
    /// This Constructor must be called by child Events during their construction. It requires the EventType of the child Event.
    BaseEvent(EventType type) : mType(type) { }
    /// This simple getter function is used internally by the engine for querying the type of an upcasted child Event. 
    inline EventType GetEventType() const { return mType; }
};

// TODO: In Progress Event.
class NLS_API_EXPORT OnKeyPressedEvent : public BaseEvent {
public:
    static const EventType eventType {EventType::OnKeyPressed };
    OnKeyPressedEvent() : BaseEvent(eventType) { }
};

//TODO: In Progress Event.
class NLS_API_EXPORT OnWinFocusChangedEvent : public BaseEvent {
private:
    GLFWwindow *mWindow { nullptr };
public:
    static const EventType eventType {EventType::OnWinFocusChanged };
    OnWinFocusChangedEvent(GLFWwindow *window) : BaseEvent(eventType), mWindow(window) { }
    inline GLFWwindow* GetActiveWindow() const { return mWindow; }
};
}