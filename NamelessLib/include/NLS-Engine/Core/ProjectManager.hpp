#pragma once

#include "NLS_API_Export.h"
#include <string>

class NLS_API_EXPORT ProjectManager {
public: 
    bool CreateNewProject(std::string projectName, std::string projectDirectoryPath);
    bool BuildProject(std::string projectName, std::string projectDirectoryPath);
};