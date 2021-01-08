#pragma once

#include "NLS-Engine/Core/NLS_API_Export.h"

#include <string>

#include <CoreCLR/hostfxr.h>
#include <CoreCLR/coreclr_delegates.h>
#include "NLS-Engine/SharpScripting/EngineDelegates.hpp"

#include "AssemblyManager.hpp"


extern "C" {
    bool NLS_API_EXPORT ExampleClassMethodBinding(Position &pos);
}


class NLS_API_EXPORT RuntimeHost {
public:
    RuntimeHost();

    void RunFunc();

private:
    void LoadHost();
    void StartNetRuntime();

    // Temp
    NLSharpDelegates::GenerateNewSharpScript_fn testFunc {};

    AssemblyManager mAssemblyManager;

    hostfxr_initialize_for_runtime_config_fn mInitializeNetFptr {nullptr};
    hostfxr_get_runtime_delegate_fn mGetDelegateFptr {nullptr};
    hostfxr_close_fn mCloseFptr {nullptr};
    load_assembly_and_get_function_pointer_fn mGetAssemblyFunctionFptr {nullptr};
};