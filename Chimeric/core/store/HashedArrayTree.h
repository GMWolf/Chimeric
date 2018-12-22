//
// Created by felix on 19/12/2018.
//

#ifndef CHIMERIC_HASHEDARRAYTREE_H
#define CHIMERIC_HASHEDARRAYTREE_H

#include <cstddef>
#include <bitset>
#include <memory>
#include <vector>
#include <deque>

namespace chimeric {


    template<class T, size_t chunkSize = 64>
    class HashedArrayTree {

        struct Chunk {

            Chunk() : _data() {
            }

            ~Chunk();

            T &operator[](size_t i);
            const T& operator[](size_t i) const;

            template<class... Args>
            T &emplace(size_t i, Args &&... args);

            void erase(size_t i);

            union {
                char _data[chunkSize * sizeof(T)]{};
                T items[chunkSize];
            };
            std::bitset<chunkSize> usage;
        };


        std::vector<std::unique_ptr<Chunk>> chunks;
        std::deque<std::unique_ptr<Chunk>> chunkPool;

        std::unique_ptr<Chunk> newChunk();

    public:
        ~HashedArrayTree();

        T &operator[](size_t i);
        const T& operator[](size_t i) const;

        template<typename ...Args>
        T &emplace(size_t i, Args &&... args);

        void erase(size_t i);

        bool has(size_t i);
    };

    template<class T, size_t chunkSize>
    auto HashedArrayTree<T, chunkSize>::newChunk() -> std::unique_ptr<Chunk> {
        if (chunkPool.empty()) {
            return std::make_unique<Chunk>();
        } else {
            auto nc = std::move(chunkPool.front());
            chunkPool.pop_front();
            return std::move(nc);
        }
    }


    template<class T, size_t chunkSize>
    T &HashedArrayTree<T, chunkSize>::operator[](size_t i) {
        size_t ci = i / chunkSize;
        size_t ii = i % chunkSize;
        return (*chunks[ci])[ii];
    }

    template<class T, size_t chunkSize>
    const T &HashedArrayTree<T, chunkSize>::operator[](size_t i) const {
        size_t ci = i / chunkSize;
        size_t ii = i % chunkSize;
        return (*chunks[ci])[ii];
    }

    template<class T, size_t chunkSize>
    template<typename... Args>
    T &HashedArrayTree<T, chunkSize>::emplace(size_t i, Args &&... args) {
        size_t ci = i / chunkSize;
        size_t ii = i % chunkSize;
        if (chunks.size() <= i) {
            chunks.resize(i + 1);
        }
        if (!chunks[ci]) {
            chunks[ci] = newChunk();
        }

        chunks[ci]->emplace(ii, args...);
        return (*chunks[ci])[ii];
    }

    template<class T, size_t chunkSize>
    void HashedArrayTree<T, chunkSize>::erase(size_t i) {
        size_t ci = i / chunkSize;
        size_t ii = i % chunkSize;

        if (chunks.size() <= ci) {
            return;
        }
        if (!chunks[ci]) {
            return;
        }

        chunks[ci]->erase(ii);

        if (chunks[ci]->usage.none()) {
            chunkPool.push_back(std::move(chunks[ci]));
            chunks[ci] = nullptr;
        }
    }

    template<class T, size_t chunkSize>
    HashedArrayTree<T, chunkSize>::~HashedArrayTree() {

    }

    template<class T, size_t chunkSize>
    bool HashedArrayTree<T, chunkSize>::has(size_t i) {
        size_t ci = i / chunkSize;
        size_t ii = i % chunkSize;
        if (chunks.size() <= ci) {
            return false;
        }
        if (!chunks[ci]) {
            return false;
        }
        return chunks[ci]->usage[ii];
    }

    template<class T, size_t chunkSize>
    T &HashedArrayTree<T, chunkSize>::Chunk::operator[](size_t i) {
        return items[i];
    }

    template<class T, size_t chunkSize>
    const T &HashedArrayTree<T, chunkSize>::Chunk::operator[](size_t i) const {
        return items[i];
    }

    template<class T, size_t chunkSize>
    template<class... Args>
    T &HashedArrayTree<T, chunkSize>::Chunk::emplace(size_t i, Args &&... args) {
        if (!usage[i]) {
            new(items + i) T(std::forward<Args>(args)...);
            usage.set(i);
        }


        return items[i];
    }

    template<class T, size_t chunkSize>
    void HashedArrayTree<T, chunkSize>::Chunk::erase(size_t i) {
        if (usage[i]) {
            items[i].~T();
            usage.reset(i);
        }
    }

    template<class T, size_t chunkSize>
    HashedArrayTree<T, chunkSize>::Chunk::~Chunk() {
        for (int i = 0; i < chunkSize; i++) {
            if (usage[i]) {
                items[i].~T();
            }
        }
    }




}

#endif //CHIMERIC_HASHEDARRAYTREE_H
