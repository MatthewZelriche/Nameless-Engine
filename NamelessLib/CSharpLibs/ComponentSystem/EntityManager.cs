using System;
using System.Collections.Generic;

namespace NLSharp {

    public class Entity {
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
        private UInt16 mEntityHeader;
        private UInt32 mEntityID;

        static private UInt32 mIDCounter;

        private Dictionary<Type, Component> mListOfComponents = new Dictionary<Type, Component>();
        private List<ScriptBase> mListOfScripts = new List<ScriptBase>();

        // Example of where to store methods of scriptcomponents.
        public System.Reflection.MethodInfo[] onCreateMethods;
        public System.Reflection.MethodInfo[] onUpdateMethods;

        public Entity() {
            mEntityID = mIDCounter++;
        }

        public ComponentType GetComponent<ComponentType>() {
            return (dynamic)mListOfComponents[typeof(ComponentType)];
        }

        public bool AddComponentToEntity(ScriptBase component) {
            mListOfScripts.Add(component);
            return true;
        }

        public bool AddComponentToEntity<ComponentType>(ComponentType component) {
            if (!typeof(ComponentType).IsSubclassOf(typeof(Component))) {
                return false;
            } else {
                mListOfComponents[typeof(ComponentType)] = component as Component;
                return true;
            }
        }
    }

/*
    public class EntityManager {
        private Dictionary<UInt32, Archetype> mArchetypeEntities = new Dictionary<UInt32, Archetype>();
        private List<Entity> mListOfWorldPoolEntities = new List<Entity>();

        private UInt32 mIdentifierCount;

        public bool CreateNewEntityArchetype() {
            if (!mArchetypeEntities.ContainsKey(mIdentifierCount)) {
                            mArchetypeEntities[mIdentifierCount] = new Archetype();
            } else {
                return false;
            }

            mIdentifierCount++;
            return true;
        }

        public Archetype GetEntityArchetype(UInt32 id) {
            return mArchetypeEntities[id];
        }

        public bool CreateNewWorldPoolEntity(Archetype entityArchetype) {
            mListOfWorldPoolEntities.Add(new Entity());
            return true;
        }

        public bool DestroyWorldPoolEntity() {


            return true;
        }
    }

    */
}