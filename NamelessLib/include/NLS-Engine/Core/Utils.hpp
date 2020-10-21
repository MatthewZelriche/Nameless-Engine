#pragma once

#include <string>

#ifdef WIN32
    #include <libloaderapi.h>
#elif __linux__
    #include <dlfcn.h>
#endif


namespace NLS::Utils {


#ifdef WIN32
    HMODULE LoadLibrary(std::string libPath) {
        return LoadLibraryExA(libPath.c_str(), NULL, 0);
    }

    FARPROC GetFunctionPtr(HMODULE library, const char *functionName) {
        return GetProcAddress(library, functionName);
    }
#elif __linux__
    void *LoadLibrary(std::string libPath) {
        return dlopen(libPath.c_str(), RTLD_NOW);
    }

    void *GetFunctionPtr(void *library, const char *functionName) {
        return dlsym(library, functionName);
    }
#endif


}