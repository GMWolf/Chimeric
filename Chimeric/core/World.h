//
// Created by felix on 18/12/2018.
//

#ifndef CHIMERIC_WORLD_H
#define CHIMERIC_WORLD_H

#include <queue>
#include "ResourceManager.h"
#include "util/dynamic_bitset.h"
#include "util/flat_set.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "FamilySubscription.h"
#include "System.h"

namespace chimeric {

    using AspectStore = HashedArrayTree<dynamic_bitset>;

    class World {
        ResourceManager resources;

        std::unordered_map<std::type_index, size_t> componentIDs;
        std::unordered_map<std::string, size_t> componentIdByName;
        std::vector<baseComponentManager*> componentManagers;
        std::unordered_map<size_t, baseComponentManager*> componentManagersByID;

        size_t nextComponentID = 0;

        //Subscription stuff
        std::vector<std::unique_ptr<FamilySubscription>> subscriptions;
        std::vector<flat_set<FamilySubscription*>> subscriptionsByBit;

        std::vector<System*> systems;

    public:
        EntityManager entities;

        World();

        void update();

        template<class T>
        size_t getComponentID() const;

        size_t getComponentID(std::type_index c) const;

        template<class T>
        void registerComponent();

        template<class T>
        T& get();

        template<class T>
        ComponentManager<T>& getComponentManager() {
            ComponentManager<T>* cm = new ComponentManager<T>(*this);
        }

        baseComponentManager* getComponentManager(const char* name);

        FamilySubscription& getSubscription(const Family& family);

        template<class T, class... Args >
        void addSystem(Args&&... args);

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
        size_t id = nextComponentID++;
        componentIDs.insert({typeid(T), id});
        componentIdByName.insert({Component<T>::name, id});
        resources.emplace<ComponentManager<T>>(*this);
        componentManagers.push_back(&resources.get<ComponentManager<T>>());
        componentManagersByID.insert({id, &resources.get<ComponentManager<T>>()});
    }

    template<class T>
    T &World::get() {
        return resources.get<T>();
    }

    template<class T>
    const T &World::getConst() {
        return resources.getConst<T>();
    }


    template<class T, class... Args>
    void chimeric::World::addSystem(Args &&... args) {
        resources.emplace<T>(*this, std::forward<Args>(args)...);
        systems.push_back(&resources.get<T>());
    }



}

#endif //CHIMERIC_WORLD_H
