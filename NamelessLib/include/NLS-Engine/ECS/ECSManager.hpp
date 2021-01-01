#pragma once

#include "ComponentHandler.hpp"
#include <map>
#include <memory>
#include <array>
#include <any>
#include <typeindex>
#include <assert.h>

#include <Log.hpp>

#include <string>

#include <robin-hood/robin_hood.h>


typedef std::vector<EntityID> EntityList;

template <typename T>
struct Pair {
    const EntityID id;
    T &component;
};

class ECSManager {
private:
    // Unordered_flat_map saved me about 28 milliseconds on a 2 Million entity iteration. 
    // Switching to ComponentHandlerBase* and static_cast saved a further 47ms.
    robin_hood::unordered_flat_map<std::type_index, ComponentHandlerBase*> componentHandlers;

    template<typename FirstArg, typename... Args>
    void GetEntitiesFromSmallestComponentHandler(int size, std::unique_ptr<EntityList> &entities, ComponentHandler<FirstArg>* firstArg, ComponentHandler<Args>*... args) {  
        // We already determined which ComponentHandler had the smallest size with std::min earlier, so now we just 
        // check each Component Handler until we find it using a recursive function and parameter packs. 
        if (size == firstArg->m_components.size()) {
            // This provides 130+ ms of performance increase.
            // You'd think that shrinking the vector so it has to re-allocate memory on the heap would make it slower.
            // Putting it seemingly anywhere else in these functions provides no boost at all, only here. 
            // And because I use shrink to fit, sizeof(entities) seems to suggest the vector does indeed return to
            // little/no heap-allocated memory, so it's not like im sacrificing memory for speed. 
            // What.
            entities->clear();
            entities->shrink_to_fit();

            // Load our EntityList with every entity from the shortest ComponentHandler
            for (auto& element : firstArg->m_components) {
                entities->emplace_back(element.first);
            }


            // When we have loaded up our entities from the shortest handler, there's no need to continue with the recursive function any longer. 
            return;
        }
        // Keep recursively calling the function until we are out of Args. 
        if constexpr (sizeof...(Args) > 0) {
            GetEntitiesFromSmallestComponentHandler(size, entities, args...);
        }
    }

    template<typename... Args>
    void CullIrrelevantEntities(EntityList::iterator id, std::unique_ptr<EntityList> &entities, bool shouldIncrement, ComponentHandler<Args>*... args) {
        // We check if the entitiyID's from the shortest ComponentHandler are also in every other requested Handler.
        // If they are, we do nothing. If they are missing from one or more other Handlers, we cull the entityID, as it
        // does not satisfy the user's request. 
        if ((args->m_components.contains(*id) && ...)) {
            shouldIncrement = true;
        } else {
            shouldIncrement = false;
            // Pop and swap entityID's to avoid costly vector erase
            *id = std::move(entities->back());
            entities->pop_back();
        }
    }

public:
    // Creates a component handler, adding it to the unordered map of all instantiated handlers. 
    template <typename T>
    void CreateComponentHandler() {
        auto type = std::type_index(typeid(ComponentHandler<T>));
        componentHandlers.emplace(type, new ComponentHandler<T>);
    }

    template <typename T, typename... VariadicArgs>
    void AddComponentToEntity(EntityID id, VariadicArgs... parameters) {
        auto type = std::type_index(typeid(ComponentHandler<T>));
        // Confirm that requested component actually has a ComponentHandler that was previously created.
        assert(componentHandlers.count(type) > 0);

        static_cast<ComponentHandler<T>*>(componentHandlers.at(type))->m_components.emplace(id, T(parameters...));
    }

    template <typename... Args>
    std::unique_ptr<EntityList> GetEntitiesWithComponents() {
        // Local EntityList needs to be a pointer so we can return it without having the local variable go out of scope. 
        std::unique_ptr<EntityList> entities = std::make_unique<EntityList>();

        // Get the size in elements of the requested Component Handler that has the fewest number of components. 
        int smallestCompSize = (std::min)({static_cast<ComponentHandler<Args>*>(componentHandlers.at(typeid(ComponentHandler<Args>)))->m_components.size()...});   

        // We pass in our EntityList by reference and the function retrieves the entityID for every component in the smallest Component Handler.
        // We get entities from the smallest Component Handler first though that when we iterate over the entities to check if they exist in the other Component Handlers, 
        // we are iterating over the least amount of entityID's neccessary. 
        GetEntitiesFromSmallestComponentHandler<Args...>(smallestCompSize, entities, static_cast<ComponentHandler<Args>*>(componentHandlers.at(typeid(ComponentHandler<Args>)))...);


        // If the user only requested one type of component, there's no need to perform the rest of the function.
        if constexpr (sizeof...(Args) == 1) {
            return entities; 
        }


        // Iterate over every entityID from the smallest ComponentHandler. 
        bool shouldIncrementIterator = true;
        for (EntityList::iterator it = entities->begin(); it != entities->end();) {
            CullIrrelevantEntities<Args...>(it, entities, &shouldIncrementIterator, static_cast<ComponentHandler<Args>*>(componentHandlers.at(typeid(ComponentHandler<Args>)))...);

            // If we didn't cull an entityID from the list, increment the iterator. 
            if (shouldIncrementIterator) {
                ++it;
            }
        }

        // Returns the list of every entityID that contains one of every Component Type requested. 
        return entities;
    }

    // Get a single component from a specified entity. 
    template <typename T>
    T& GetComponent(const EntityID &id) {
        return static_cast<ComponentHandler<T>*>(componentHandlers.at(typeid(ComponentHandler<T>)))->m_components.at(id);
    }

    template <typename T>
    typename robin_hood::unordered_flat_map<EntityID, T>& GetComponents() {
        return static_cast<ComponentHandler<T>*>(componentHandlers.at(typeid(ComponentHandler<T>)))->m_components;
    }

    template <typename T>
    const typename robin_hood::unordered_flat_map<EntityID, T>::iterator GetComponentHandlerBegin() {
        return static_cast<ComponentHandler<T>*>(componentHandlers.at(typeid(ComponentHandler<T>)))->m_components.begin();
    }

    template <typename T>
    const typename robin_hood::unordered_flat_map<EntityID, T>::iterator GetComponentHandlerEnd() {
        return static_cast<ComponentHandler<T>*>(componentHandlers.at(typeid(ComponentHandler<T>)))->m_components.end();
    }
};

