#pragma once

#include <robin-hood/robin_hood.h>
#include <vector>
#include <typeindex>

#include "ComponentTypes.hpp"

template<typename ComponentType>
class ComponentHandler : public ComponentHandlerBase {
public:
    robin_hood::unordered_flat_map<EntityID, ComponentType> m_components;
};

