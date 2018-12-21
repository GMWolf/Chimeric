//
// Created by felix on 19/12/2018.
//

#ifndef CHIMERIC_COMPONENTMANAGER_H
#define CHIMERIC_COMPONENTMANAGER_H

#include <cstddef>
#include <utility>
#include "Storage.h"

namespace chimeric {
    template<class T>
    class ComponentManager {
        Store<T> store;
    public:
        T& operator[](size_t id);
        bool has(size_t id);

        template<class... Args>
        T& emplace(size_t id, Args&&... args);
    };

    template<class T>
    T &ComponentManager<T>::operator[](size_t id) {
        return store[id];
    }

    template<class T>
    bool ComponentManager<T>::has(size_t id) {
        return store.has(id);
    }

    template<class T>
    template<class... Args>
    T &ComponentManager<T>::emplace(size_t id, Args&&... args) {
        return store.emplace(id, std::forward<Args>(args)...);
    }

}

#endif //CHIMERIC_COMPONENTMANAGER_H
