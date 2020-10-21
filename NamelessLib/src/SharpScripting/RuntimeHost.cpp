#include "NLS-Engine/SharpScripting/RuntimeHost.hpp"

#include <stdio.h>
#include <assert.h>
#include <string>

#include <Log.hpp>
#include <NetHost/nethost.h>

#include "NLS-Engine/Core/Utils.hpp"
#include "NLS-Engine/SharpScripting/EngineDelegates.hpp"

RuntimeHost::RuntimeHost() {
    LoadHost();
    StartNetRuntime();

    NLSharpDelegates::GenerateNewSharpScript_fn function = mAssemblyManager.GetCustomCSharpFuncPointer<NLSharpDelegates::GenerateNewSharpScript_fn>(
                                    mGetAssemblyFunctionFptr, "NLSharp.dll", "NLSharp", "NLSharp", "Roslyn", "GenerateScript");

    if (function) {
        function(12);
    }
}

void RuntimeHost::LoadHost() {
    char buffer[4096];
    size_t bufferSize = sizeof(buffer) / sizeof(char);

    int errorCode = get_hostfxr_path(buffer, &bufferSize, nullptr);
    if (errorCode != 0) {
        NLSLOG::Error("Engine", "Failed to find hostfxr library! Aborting...");
        std::exit(-1);
    }

    std::string fxrPath(buffer);
    void* fxrLib = NLS::Utils::LoadLibrary(fxrPath);

    if (!fxrLib) {
        NLSLOG::Error("Engine", "Failed to load hostfxr library into memory!"
                        "Aborting...");
        std::exit(-1);
    }

    mInitializeNetFptr = (hostfxr_initialize_for_runtime_config_fn)
                        NLS::Utils::GetFunctionPtr(fxrLib, 
                        "hostfxr_initialize_for_runtime_config");
    mGetDelegateFptr = (hostfxr_get_runtime_delegate_fn)
                        NLS::Utils::GetFunctionPtr(fxrLib,
                        "hostfxr_get_runtime_delegate");
    mCloseFptr = (hostfxr_close_fn)NLS::Utils::GetFunctionPtr(fxrLib, "hostfxr_close");

    if (!mInitializeNetFptr || !mGetDelegateFptr || !mCloseFptr) {
        NLSLOG::Error("Engine", "Failed to load critical net core function. Aborting...");
        std::exit(-1);
    }
}

void RuntimeHost::StartNetRuntime() {
    void *tempFptr = nullptr;
    hostfxr_handle fxrHandle = nullptr;

    std::string configPath("NLS.runtimeconfig.json");
    int errorCode = mInitializeNetFptr(configPath.c_str(), nullptr, &fxrHandle);
    if (errorCode != 0 || !fxrHandle) {
        NLSLOG::Error("Engine", "Could not start .NET Runtime Host! Aborting...");
        std::exit(-1);
    }

    errorCode = mGetDelegateFptr(fxrHandle, 
                                hdt_load_assembly_and_get_function_pointer,
                                &tempFptr);
    
    mGetAssemblyFunctionFptr = (load_assembly_and_get_function_pointer_fn)tempFptr;

    if (errorCode != 0 || !mGetAssemblyFunctionFptr) {
        NLSLOG::Error("Engine", "Failed to load critical net core function. Aborting...");
        std::exit(-1);
    }
}