#pragma once

#include <unordered_map>
#include <string>
#include <set>

#include "NLS-Engine/Core/NLS_API_Export.h"

namespace NLS::INPUT {

class NLS_API_EXPORT KeyBindingSet {
private:
    // A map of "actions" and "keycodes".
    std::unordered_map<std::string, int> mKeyBindings;
    // This set holds every keycode thats currently bound for this set, to ensure a keycode isn't bound more than once.
    std::set<int> mRawKeyCodeValues;
    /**
    * @brief Opens controls.ini config file and loads values into the KeyBindingSet.
    * 
    * This functions does several error-checks, including to confirm that the requested subsection exists, and that
    * the file doesn't contain any non-existant keybinds.
    * 
    * @param setName The name of the Keybinding Subsection to load from. This allows multiple KeyBindingSets to be saved in controls.ini at once. 
    */
    void LoadSetFromFile(const std::string &setName = "Main");
public:
    /**
    * @brief Constructs a new KeyBindingSet with a set of user-defined keybind actions. 
    * 
    * @param listOfValidKeyBinds An Initializer list to give the object an arbitrary number of keybind actions, eg "Shoot", "Jump", "Crouch".
    */
    KeyBindingSet(std::initializer_list<std::string> listOfValidKeyBinds);
    /**
    * @brief Sets a new Keycode value to a specific keybind action. 
    * 
    * Note: This does not save the changes to file. Use SaveSetToFile for this.
    * 
    * @param keybindName The name of the keybind action to change. 
    * @param keycode The new keycode to assign to the keybind action.
    */
    void BindNewKeycode(const std::string &keybindName, int keycode);
    /**
    * @brief Saves the current keybindings to controls.ini
    * 
    * @param setName The name of the Keybinding Subsection to save to. This allows multiple KeyBindingSets to be saved in controls.ini at once. 
    */
    void SaveSetToFile(const std::string &setName = "Main");
};
}
