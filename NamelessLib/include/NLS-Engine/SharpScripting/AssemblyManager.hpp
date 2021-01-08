#pragma once

#include "NLS-Engine/Core/NLS_API_Export.h"

#include <CoreCLR/coreclr_delegates.h>
#include <Log.hpp>

#include "NLS-Engine/Core/Utils.hpp"

#include <string>

class NLS_API_EXPORT AssemblyManager {
public:
    
    template <typename T>
    T GetCustomCSharpFuncPointer(load_assembly_and_get_function_pointer_fn RetrieveFnPointer, 
                                    std::string assemblyPath, 
                                    std::string assemblyName,
                                    std::string namespaceName,
                                    std::string className, 
                                    std::string methodName) {

        T function = nullptr;

        std::string assemblyQualifiedName = namespaceName + "." + className + ", " + assemblyName;

        int errorCode = RetrieveFnPointer(NLS::Utils::ConvertStringToWString(assemblyPath).c_str(),
            NLS::Utils::ConvertStringToWString(assemblyQualifiedName).c_str(),
            NLS::Utils::ConvertStringToWString(methodName).c_str(),
            UNMANAGEDCALLERSONLY_METHOD,
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