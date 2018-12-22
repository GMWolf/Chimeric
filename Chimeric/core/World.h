//
// Created by felix on 18/12/2018.
//

#ifndef CHIMERIC_WORLD_H
#define CHIMERIC_WORLD_H

#include <queue>
#include "ResourceManager.h"
#include "util/dynamic_bitset.h"
#include "EntityManager.h"
#include "ComponentManager.h"

namespace chimeric {

    class World {
        ResourceManager resources;

        std::unordered_map<std::type_index, size_t> componentIDs;

        std::vector<baseComponentManager*> componentManagers;

        size_t nextComponentID = 0;

    public:
        EntityManager entities;

        void update();

        template<class T>
        size_t getComponentID() const;

        size_t getComponentID(std::type_index c) const;

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
    size_t World::getComponentID() const {
        return componentIDs.at(typeid(T));
    }

    template<class T>
    void World::registerComponent() {
        componentIDs.insert({typeid(T), nextComponentID++});
        resources.emplace<ComponentManager<T>>(*this);
        componentManagers.push_back(&resources.get<ComponentManager<T>>());
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
