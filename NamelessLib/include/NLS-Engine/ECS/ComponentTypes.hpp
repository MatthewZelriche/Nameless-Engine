#pragma once

#include <stdint.h>

typedef uint64_t EntityID;

class ComponentHandlerBase {

};

class ComponentBase {

};

class ScriptComponent : ComponentBase {
private:
    EntityID id;
};

