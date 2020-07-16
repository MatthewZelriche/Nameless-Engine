#include "NLS-Engine/IO/KeyBindingSet.hpp"
#include "NLS-Engine/IO/ReadWriteFile.hpp"

#include <Log.hpp>
#include <vector>
#include <iniparser.hpp>

NLS::INPUT::KeyBindingSet::KeyBindingSet(std::initializer_list<std::string> listOfValidKeyBinds) {
    for (auto &actionName : listOfValidKeyBinds) { 
        // Fill the map with the list of key commands the game has specified.
        // Since no keyset has loaded yet, set every key to invalid key. 
        mKeyBindings[actionName] = -1;
    }
    LoadSetFromFile();
}

void NLS::INPUT::KeyBindingSet::LoadSetFromFile(const std::string &setName) {
    auto config = NLS::IO::ReadConfigFile("controls.ini");
    INI::Section *subsection = config.GetSection("Keybinding")->GetSubSection(setName);

    // Check to confirm the requested KeyBinding set exists in controls.ini
    if (subsection->ValuesSize() == 0) {
        NLSLOG::Error("Engine", "Keybinding set '{}' does not exist in controls.ini!", subsection->Name());
        throw std::runtime_error("Fatal error.");
    }

    for (INI::Section::values_iter it = subsection->ValuesBegin(); it != subsection->ValuesEnd(); ++it) {
        // Check to confirm the actions in controls.ini are valid game actions. 
        if (mKeyBindings.count(it->first)) {

            // Test if the keycode is entirely unique to this keybinding set. 
            if(mRawKeyCodeValues.insert(it->second.AsInt()).second) {
                mKeyBindings[it->first] = it->second.AsInt();
            } else {
                NLSLOG::Error("Engine", "Keycode '{}' defined for action '{}' in controls.ini, but this keycode has already been defined!", it->second.AsInt(), it->first);
                throw std::runtime_error("Fatal error.");
            }
        } else {
            NLSLOG::Warn("Engine", "Keybind '{}' read from controls.ini but does not exist!", it->first);
        }
    }
}

void NLS::INPUT::KeyBindingSet::BindNewKeycode(const std::string &keybindName, int keycode) {
    // Confirm the action actually exists.
    if (mKeyBindings.count(keybindName)) {
        // We need to first erase the original value from our raw set to "free" it to be used again in the future. 
        mRawKeyCodeValues.erase(mKeyBindings[keybindName]);

        // Confirm that the newly requested keycode isn't already in use. 
        if(mRawKeyCodeValues.insert(keycode).second) {
            mKeyBindings[keybindName] = keycode;
        } else {
            NLSLOG::Warn("Engine", "Tried to set keycode '{}' for action '{}', but this keycode is already in use!", keycode, keybindName);
        }
    }
}

void NLS::INPUT::KeyBindingSet::SaveSetToFile(const std::string &setName) {
    auto config = NLS::IO::ReadConfigFile("controls.ini");

    INI::Section *section = config.GetSection("Keybinding")->GetSubSection(setName);
    if (section->ValuesSize() == 0) {
        NLSLOG::Error("Engine", "Keybinding set '{}' does not exist in controls.ini!", section->Name());
        throw std::runtime_error("Fatal error.");
    }
    for(auto &keybind : mKeyBindings) {
        section->SetValue(keybind.first, keybind.second);
    }

    config.Save("controls.ini");
}