#include "NLS-Engine/IO/ReadWriteFile.hpp"

INI::File NLS::IO::ReadConfigFile(const char *fileName) {
    INI::File config;
    if (!config.Load(fileName)) {
        
        // Error check to look for missing config files, syntax errors, etc.
        auto error = config.LastResult();
        if (error == -1) {
            NLSLOG::Error("Engine", "{}", error.GetErrorDesc());
            throw std::runtime_error("Fatal error.");
        } else {
            NLSLOG::Warn("Engine", "{}", error.GetErrorDesc());
        }
    }

    // Is it more performant to use std::move here? Since I can't return a local variable as a reference. 
    return std::move(config);
}