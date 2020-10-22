#pragma once

#include <string>
#include <locale>
#include <codecvt>
#include <NetHost/nethost.h>

#ifdef __linux__
    #include <dlfcn.h>
#else
    #include <Windows.h>
    #include <libloaderapi.h>
#endif


namespace NLS::Utils {


    std::string ConvertWideCharArrayToString(const char_t *input);

    std::wstring ConvertStringToWString(std::string input);


#ifdef __linux__
    void* LoadLibrary(std::string libPath);

    void* GetFunctionPtr(void* library, const char* functionName);
#else
    HMODULE LoadLibrary(std::string libPath);

    FARPROC GetFunctionPtr(void* library, const char* functionName);
#endif


}