#include "NLS-Engine/Core/Utils.hpp"


namespace NLS::Utils {


    std::string ConvertWideCharArrayToString(const char_t *input) {
#if __linux__
        return std::string(input);
#else 
        std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
        return converter.to_bytes(input);
#endif
    }

    std::wstring ConvertStringToWString(std::string input) {
#if __linux__
        return input;
#else
        std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
        return converter.from_bytes(input);
#endif
    }


#ifdef __linux__
    void* LoadLibrary(std::string libPath) {
        return dlopen(libPath.c_str(), RTLD_NOW);
    }

    void* GetFunctionPtr(void* library, const char* functionName) {
        return dlsym(library, functionName);
    }
#else
    HMODULE LoadLibrary(std::string libPath) {
        return LoadLibraryExA(libPath.c_str(), NULL, 0);
    }

    FARPROC GetFunctionPtr(void* library, const char* functionName) {
        return GetProcAddress((HMODULE)library, functionName);
    }
#endif


}