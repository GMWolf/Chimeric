//
// Created by felix on 18/12/2018.
//

#ifndef CHIMERIC_RESOURCEMANAGER_H
#define CHIMERIC_RESOURCEMANAGER_H

#include <unordered_map>
#include <typeindex>
#include <tuple>

namespace chimeric {

    class ResourceManager {

        struct handle {
            template<class T>
            explicit handle(T *p) : p(p), destroy([](void *p) { delete static_cast<T *>(p); }) {
            }

            ~handle() {
                destroy(p);
            }

            void *p;

            void (*destroy)(void *);
        };

    public:
        template<class T>
        T &get();

        template<class T>
        const T& getConst();

        template<class T>
        const T &get() const;

        template<class T, class... Args>
        void emplace(Args&&... args);

    protected:
        std::unordered_map<std::type_index, handle> store;
    };

    template<class T>
    T &ResourceManager::get() {
        return *static_cast<T *>(store.at(typeid(T)).p);
    }

    template<class T>
    const T &ResourceManager::get() const {
        return *static_cast<T *>(store.at(typeid(T)).p);
    }

    template<class T, class... Args>
    void ResourceManager::emplace(Args&&... args) {
        store.emplace(std::piecewise_construct,
                std::forward_as_tuple(typeid(T)),
                std::forward_as_tuple(new T(args...)));
        //store.try_emplace(typeid(T), new T(std::forward<Args>(args)...));
    }

    template<class T>
    const T &ResourceManager::getConst() {
        return get<T>();
    }

}

#endif //CHIMERIC_RESOURCEMANAGER_H
