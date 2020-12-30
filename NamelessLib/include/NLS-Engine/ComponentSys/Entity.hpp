#pragma once

#include "NLS-Engine/Core/NLS_API_Export.h"

#include <stdint.h>
#include <vector>

#include "Component.hpp"

class NLS_API_EXPORT Entity {
private:
    /* 
    *
    *                 mEntityHeader                         mEntityID   
    *                       |                                   |
    *           /----------------------\                /--------------\
    *           0x  F               FFF                  0x  FFFFFFFF
    *             \__/            \____/                    \________/
    *              |                |                           |
    *       Storage Group ID      ModID      Unique ID of entity Archetype or World Instance
    * 
    * mEntityHeader stores a value in the form of 0xFFFF.
    * The first nibble 0xF000 encodes the type of storage group that entity belongs to.
    * 0 is the Archetype group, 1 is the WorldPool group, and 2 is the SaveFile group. The other values 3-15 are unused. 
    * 
    * The other three nibbles 0x0FFF is a modID value. Each mod is assigned a value between 000 - FFF on launch.
    */
    uint16_t mEntityHeader {0};
    uint32_t mEntityID {0};

    std::vector<Component*> mListOfComponents;
};


class NLS_API_EXPORT EntityManager {
private:
    std::vector<Entity> mListOfEntityArchetypes;
    std::vector<Entity> mListOfWorldPoolEntities;

public:

    bool CreateNewEntityArchetype();
    bool CreateNewWorldPoolEntity();

    bool DestroyWorldPoolEntity();
};