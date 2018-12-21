//
// Created by felix on 18/12/2018.
//

#ifndef CHIMERIC_WORLD_H
#define CHIMERIC_WORLD_H

#include <queue>
#include "ResourceManager.h"
#include "ComponentManager.h"
#include "util/dynamic_bitset.h"
#include "EntityManager.h"

namespace chimeric {

    class World {
        ResourceManager resources;

        std::unordered_map<std::type_index, size_t> componentIDs;
        size_t nextComponentID = 0;

        EntityManager entities;

    public:
        template<class T>
        size_t getComponentID();

        template<class T>
        void registerComponent();

        template<class T>
        T& get();

        template<class T>
        const T& getConst();

        size_t create();
        void destroy(size_t id);
    };


    template<class T>
    size_t World::getComponentID() {
        return componentIDs[typeid(T)];
    }

    template<class T>
    void World::registerComponent() {
        componentIDs.insert({typeid(T), nextComponentID++});
        resources.emplace<ComponentManager<T>>();
    }

    template<class T>
    T &World::get() {
        return resources.get<T>();
    }

    template<class T>
    const T &World::getConst() {
        return resources.getConst<T>();
    }

}

#endif //CHIMERIC_WORLD_H
