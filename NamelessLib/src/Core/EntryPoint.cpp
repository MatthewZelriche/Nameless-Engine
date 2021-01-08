#include "NLS-Engine/Core/EntryPoint.hpp"
#include "NLS-Engine/Core/DefaultEngine.hpp"

int NLSMain() {
    DefaultEngine engine;
    engine.Run();
    return 0;
}