#pragma once

#include "NLS-Engine/Core/NLS_API_Export.h"

#include <string>

#include <CoreCLR/hostfxr.h>
#include <CoreCLR/coreclr_delegates.h>

#include "AssemblyManager.hpp"

class NLS_API_EXPORT RuntimeHost {
public:
    RuntimeHost();

    bool CreateNewProject(std::string projectName) { return mAssemblyManager.CreateNewProject(projectName); }

private:
    void LoadHost();
    void StartNetRuntime();

    AssemblyManager mAssemblyManager;

    hostfxr_initialize_for_runtime_config_fn mInitializeNetFptr {nullptr};
    hostfxr_get_runtime_delegate_fn mGetDelegateFptr {nullptr};
    hostfxr_close_fn mCloseFptr {nullptr};
    load_assembly_and_get_function_pointer_fn mGetAssemblyFunctionFptr {nullptr};
};