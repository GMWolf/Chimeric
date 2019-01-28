//
// Created by felix on 19/12/2018.
//

#ifndef CHIMERIC_VECSTORE_H
#define CHIMERIC_VECSTORE_H

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <memory>

namespace chimeric {

    template<class T,
            class Allocator = std::allocator<T>,
            class BAllocator = std::allocator<bool>>
    class VecStore {
        Allocator allocator;
        BAllocator bAllocator;

        T* array = nullptr;
        bool* usage = nullptr;
        size_t capacity = 0;

        void grow(size_t size);

    public:

        VecStore();
        ~VecStore();

        T &operator[](size_t i);

        template<typename ...Args>
        T &emplace(size_t i, Args &&... args);

        void erase(size_t i);

        bool has(size_t i);
    };

    template<class T, class A, class BA>
    void VecStore<T, A, BA>::grow(size_t size) {

        if (size > capacity) {
            auto _array = array;
            auto _usage = usage;

            array = allocator.allocate(size);
            usage = bAllocator.allocate(size);

            if (_array) {
                memcpy(array, _array, capacity * sizeof(T));
                delete _array;
            }
            if (_usage) {
                memcpy(usage, _usage, capacity * sizeof(bool));
                delete _usage;
            }

            std::fill(usage + capacity, usage + size, false);

            capacity = size;
        }
    }

    template<class T, class A, class BA>
    VecStore<T, A, BA>::VecStore() = default;

    template<class T, class A, class BA>
    VecStore<T, A, BA>::~VecStore() {
        for(int i = 0; i < capacity; i++) {
            if (usage[i]) {
                array[i].~T();
            }
        }

        delete array;
        delete usage;
    }

    template<class T, class A, class BA>
    T &VecStore<T, A, BA>::operator[](size_t i) {
        return array[i];
    }

    template<class T, class A, class BA>
    template<typename... Args>
    T &VecStore<T, A, BA>::emplace(size_t i, Args &&... args) {
        if (capacity <= i) {
            grow(static_cast<size_t>((i + 1) * 1.5));
        }

        if (!usage[i]) {
            new (array + i) T(std::forward<Args>(args)...);
            usage[i] = true;
        }

        return array[i];
    }

    template<class T, class A, class BA>
    void VecStore<T, A, BA>::erase(size_t i) {
        if (capacity > i && usage[i]) {
            array[i].~T();
            usage[i] = false;
        }
    }

    template<class T, class A, class BA>
    bool VecStore<T, A, BA>::has(size_t i) {
        return (capacity > i &&  usage[i]);
    }


}

#endif //CHIMERIC_VECSTORE_H
