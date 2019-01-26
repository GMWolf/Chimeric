//
// Created by felix on 19/12/2018.
//

#ifndef CHIMERIC_COMPONENTMANAGER_H
#define CHIMERIC_COMPONENTMANAGER_H

#include <cstddef>
#include <utility>
#include <typeindex>
#include "util/flat_set.h"
#include "util/dynamic_bitset.h"
#include "Component.h"

namespace chimeric {

    class World;
    class baseComponentManager {
        friend World;
    protected:
        explicit baseComponentManager(World& world, std::type_index c);
        dynamic_bitset batchAdd{};
        dynamic_bitset batchRemove{};
        size_t bit;

    public:
        void processBatchTasks(World& world);
        virtual void processBatchRemove() = 0;
        void remove(size_t id);
    };

    template<class T>
    class ComponentManager : public baseComponentManager {
        Store<T> store;
    public:
        explicit ComponentManager(World& world) : baseComponentManager(world, typeid(T)) {}
        ComponentManager(const ComponentManager& o) = delete;

        T& operator[](size_t id);
        bool has(size_t id);
        bool available(size_t id);

        template<class... Args>
        T& emplace(size_t id, Args&&... args);

        void processBatchRemove() override;
    };

    template<class T>
    T& ComponentManager<T>::operator[](size_t id) {
        return store[id];
    }

    template<class T>
    bool ComponentManager<T>::has(size_t id) {
        return store.has(id) && !batchRemove.test(id);
    }

    template<class T>
    template<class... Args>
    T &ComponentManager<T>::emplace(size_t id, Args&&... args) {

        if (batchRemove.test(id)) {
            store.erase(id);
            batchRemove.reset(id);
        }

        batchAdd.set(id);
        return store.emplace(id, std::forward<Args>(args)...);
    }

    template<class T>
    void ComponentManager<T>::processBatchRemove() {
        batchRemove.foreachset([this](size_t e){
            store.erase(e);
        });
    }

    template<class T>
    bool ComponentManager<T>::available(size_t id) {
        return store.has(id);
    }

}

#endif //CHIMERIC_COMPONENTMANAGER_H
