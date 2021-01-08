#include "NLS-Engine/SharpScripting/RuntimeHost.hpp"

#include <stdio.h>
#include <assert.h>
#include <string>

#include <Log.hpp>
#include <NetHost/nethost.h>

#include "NLS-Engine/Core/Utils.hpp"
#include "NLS-Engine/ComponentSys/Component.hpp"
#include "NLS-Engine/Core/SubsystemLocator.hpp"
#include "NLS-Engine/Rendering/WindowManager.hpp"


// Bindings test
extern "C" {
    bool NLS_API_EXPORT ExampleClassMethodBinding(Position &pos) {
        NLSLOG::Info("Engine", "Test: {}", pos.x);
        return SubsystemLocator::GetWindowManager().AllWindowsClosed();
    }
}


RuntimeHost::RuntimeHost() {
    LoadHost();
    StartNetRuntime();

    // Test retrieving a function from NLSharp. 
    NLSharpDelegates::GenerateNewSharpScript_fn function = mAssemblyManager.GetCustomCSharpFuncPointer<NLSharpDelegates::GenerateNewSharpScript_fn>(
                                    mGetAssemblyFunctionFptr, "NLSharp/NLSharp.dll", "NLSharp", "NLSharp", "ScriptCreator", "CreateNewScriptComponent");

    
    testFunc = function;
}

void RuntimeHost::RunFunc() {
        if (testFunc) {
            std::string scriptName = "MyNewScript";
            std::string projectName = "MyTestProject";
            testFunc(NLS::Utils::ConvertStringToWString(scriptName).c_str(), NLS::Utils::ConvertStringToWString(projectName).c_str());
        }
}

void RuntimeHost::LoadHost() {
    char_t buffer[4096];
    size_t bufferSize = sizeof(buffer) / sizeof(char);

    // Hardcoding like this needed for using multiple different .net versions?
    //const get_hostfxr_parameters params {sizeof(hostfxr_initialize_parameters), L"/home/nerevar/.dotnet/dotnet", L"/home/nerevar/.dotnet" };
    int errorCode = get_hostfxr_path(buffer, &bufferSize, nullptr);
    if (errorCode != 0) {
        NLSLOG::Error("Engine", "Failed to find hostfxr library! Aborting...");
        std::exit(-1);
    }

    std::string fxrPath = NLS::Utils::ConvertWideCharArrayToString(buffer);
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

    std::string configPath("NLSharp/NLS.runtimeconfig.json");
    int errorCode = mInitializeNetFptr(NLS::Utils::ConvertStringToWString(configPath).c_str(), nullptr, &fxrHandle);
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