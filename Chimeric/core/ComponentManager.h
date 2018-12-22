//
// Created by felix on 19/12/2018.
//

#ifndef CHIMERIC_COMPONENTMANAGER_H
#define CHIMERIC_COMPONENTMANAGER_H

#include <cstddef>
#include <utility>
#include "util/flat_set.h"
#include "Storage.h"

namespace chimeric {

    class baseComponentManager {
    protected:
        flat_set<size_t> batchRemove;

    public:
        virtual void processBatchTasks() = 0;
        void remove(size_t id);
    };

    template<class T>
    class ComponentManager : public baseComponentManager {
        Store<T> store;
    public:
        ComponentManager() = default;
        ComponentManager(const ComponentManager& o) = delete;

        T& operator[](size_t id);
        bool has(size_t id);
        bool available(size_t id);

        template<class... Args>
        T& emplace(size_t id, Args&&... args);

        void processBatchTasks() override;
    };

    template<class T>
    T& ComponentManager<T>::operator[](size_t id) {
        return store[id];
    }

    template<class T>
    bool ComponentManager<T>::has(size_t id) {
        return store.has(id) && !batchRemove.contains(id);
    }

    template<class T>
    template<class... Args>
    T &ComponentManager<T>::emplace(size_t id, Args&&... args) {
        auto p = batchRemove.find(id);
        if (p != batchRemove.end()) {
            batchRemove.erase(p);
            store.erase(id);
        }

        return store.emplace(id, std::forward<Args>(args)...);
    }

    template<class T>
    void ComponentManager<T>::processBatchTasks() {
        for(auto e : batchRemove) {
            store.erase(e);
        }
        batchRemove.clear();
    }

    template<class T>
    bool ComponentManager<T>::available(size_t id) {
        return store.has(id);
    }

}

#endif //CHIMERIC_COMPONENTMANAGER_H
