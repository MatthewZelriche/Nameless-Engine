#pragma once

#include "NLS-Engine/Core/NLS_API_Export.h"
#include "NLS-Engine/EventSystem/EventCapable.hpp"
#include "NLS-Engine/Rendering/GLContext.hpp"

namespace NLS::Core {
/**
* @brief Abstract base class that the user's main Game class should inherit from.
*/
class NLS_API_EXPORT IGameTemplate : public EVENT::EventCapable {
public:
    /// This function should be called from your derived Game class to begin running the game. 
    virtual void Run() final;
private:
    void InternalUpdate();

    RENDERING::GLContext mGLContext;
protected:
    IGameTemplate() = default;
    /// OnUpdate must be implemented by the child class. It runs as fast as possible, and would be used for things like rendering.
    virtual void OnUpdate() = 0;
    /// OnFixedUpdate is optional, but should likely be implemented. It runs at a fixed timestep. 
    virtual void OnFixedUpdate() { };
};
}