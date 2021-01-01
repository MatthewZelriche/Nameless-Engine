#pragma once

#include "CoreCLR/coreclr_delegates.h"

#include "NLS-Engine/ComponentSys/Component.hpp"


namespace NLSharpDelegates {

// TODO: Cross-platform this so i dont have to deal with wchar_t. How?
#ifdef __linux__
	typedef void (CORECLR_DELEGATE_CALLTYPE *GenerateNewSharpScript_fn)(const char *scriptName, const char *projectName);
#else
	typedef void (CORECLR_DELEGATE_CALLTYPE* GenerateNewSharpScript_fn)(const wchar_t* scriptName, const wchar_t* projectName);
#endif


}