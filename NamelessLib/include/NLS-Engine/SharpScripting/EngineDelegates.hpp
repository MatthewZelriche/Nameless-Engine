#pragma once

#include "CoreCLR/coreclr_delegates.h"

#include "NLS-Engine/ComponentSys/Component.hpp"


namespace NLSharpDelegates {

typedef void (CORECLR_DELEGATE_CALLTYPE *GenerateNewSharpScript_fn)(const char *scriptName, const char *projectName);


}