#pragma once

#include <memory>
#include <list>

#include "NLS-Engine/Core/NLS_API_Export.h"
#include "NLS-Engine/EventSystem/EventCapable.hpp"
#include "NLS-Engine/Rendering/Window.hpp"

namespace NLS::RENDERING {

/**
* @brief Static class that manages created Window instances. Construct Windows through this class.
*  
* To ensure multi-window functionality, WindowManager exists to track instances of alive Window objects. 
* You can only create a Window through WindowManager, to ensure the resultant window is properly tracked.
* 
* @see Window
*/
class NLS_API_EXPORT WindowManager : EVENT::EventCapable {
private:
    static std::list<std::shared_ptr<Window>> sListOfWindows;
    static void GetActiveWindow(GLFWwindow* window, int focused);
public:
    /**
    * @brief Constructs a Window object and adds it to a list of tracked windows. 
    * 
    * @param windowTitle Name to give the newly constructed window. TODO: In the future use some kind of custom struct of initialization data.
    * 
    * @returns A weak pointer to the newly constructed Window Object.
    */
    static std::weak_ptr<Window> ConstructWindow(const char *windowTitle);
    /**
    * @brief Tracks whether there are any alive Window objects left. Usually used to determine if application should close.
    * 
    * @returns True if there are no more living Window objects, false otherwise. 
    */
    static bool AllWindowsClosed();

    static const std::list<std::shared_ptr<Window>>& GetListOfWindows();
};
}