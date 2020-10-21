#pragma once

#include "NLS-Engine/Core/NLS_API_Export.h"

#include <CoreCLR/coreclr_delegates.h>
#include <Log.hpp>

#include <string>

class NLS_API_EXPORT AssemblyManager {
public:
    bool CreateNewProject(std::string projectName);
    
    template <typename T>
    T GetCustomCSharpFuncPointer(load_assembly_and_get_function_pointer_fn RetrieveFnPointer, 
                                    std::string assemblyPath, 
                                    std::string assemblyName,
                                    std::string namespaceName,
                                    std::string className, 
                                    std::string methodName) {

        T function = nullptr;

        std::string assemblyQualifiedName = namespaceName + "." + className + ", " + assemblyName;

        int errorCode = RetrieveFnPointer(assemblyPath.c_str(), 
            assemblyQualifiedName.c_str(), 
            methodName.c_str(), 
            (namespaceName + "." + className + "+" + methodName + "Delegate" + ", " + assemblyName).c_str(), 
            nullptr, (void**)&function);

        if (errorCode != 0) {
            NLSLOG::Warn("Engine", "Failed to load C# Function {} in {}", methodName, assemblyQualifiedName);
            return nullptr;
        }

        return function;
    }


    //bool CreateNewScript();
    //bool CompileAssembly();
};