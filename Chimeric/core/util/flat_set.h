//
// Created by felix on 21/12/2018.
//

#ifndef CHIMERIC_FLAT_SET_H
#define CHIMERIC_FLAT_SET_H

#include <vector>
#include <algorithm>
#include<set>

namespace chimeric {

    template<class T, class Allocator = std::allocator<T>>
    class flat_set {
        std::vector<T, Allocator> vec;

    public:
        using iterator = typename std::vector<T>::iterator;
        using const_iterator = typename std::vector<T>::const_iterator;


        flat_set() = default;
        flat_set(std::initializer_list<T> il);

        iterator begin();
        const_iterator begin() const;
        const_iterator cbegin() const;

        iterator end();
        const_iterator end() const;
        const_iterator cend() const;

        bool contains(const T& value) const;

        std::pair<iterator, bool> insert(const T& value);
        void insert(std::initializer_list<T> ilist);


        iterator erase(iterator pos);

        void clear();
        size_t count() const;
        iterator find(const T& value);
        const_iterator find(const T& value) const;

        bool operator==(const flat_set<T>& o) const;
    };


    template<class T, class A>
    flat_set<T, A>::flat_set(std::initializer_list<T> il) {
        for(auto& v : il) {
            insert(v);
        }
    }

    template<class T, class A>
    bool flat_set<T, A>::contains(const T & value) const {
        return std::find(begin(), end(), value) != end();
    }

    template<class T, class A>
    auto flat_set<T, A>::insert(const T &value) -> std::pair<iterator, bool> {
        auto f = std::find(vec.begin(), vec.end(), value);
        if (f != vec.end()) {
            return std::make_pair(f, false);
        }

        vec.push_back(value);
        return std::make_pair(vec.end() - 1, true);
    }

    template<class T, class A>
    auto flat_set<T, A>::erase(iterator pos) -> iterator {
        std::iter_swap(pos, vec.end()-1);
        vec.resize(vec.size() - 1);
        return pos;
    }

    template<class T, class A>
    void flat_set<T, A>::clear() {
        vec.clear();
    }

    template<class T, class A>
    size_t flat_set<T, A>::count() const {
        return vec.size();
    }

    template<class T, class A>
    auto flat_set<T, A>::find(const T& value) -> iterator {
        return std::find(begin(), end(), value);
    }

    template<class T, class A>
    auto flat_set<T, A>::find(const T &value) const -> const_iterator {
        return std::find(cbegin(), cend(), value);
    }

    template<class T, class A>
    auto flat_set<T, A>::begin() -> iterator {
        return vec.begin();
    }

    template<class T, class A>
    auto flat_set<T, A>::cbegin() const -> const_iterator {
        return vec.cbegin();
    }

    template<class T, class A>
    auto flat_set<T, A>::end() -> iterator {
        return vec.end();
    }

    template<class T, class A>
    auto flat_set<T, A>::cend() const -> const_iterator {
        return vec.cend();
    }

    template<class T, class A>
    auto flat_set<T, A>::begin() const -> const_iterator {
        return vec.cbegin();
    }

    template<class T, class A>
    auto flat_set<T, A>::end() const -> const_iterator {
        return vec.cend();
    }

    template<class T, class A>
    bool flat_set<T, A>::operator==(const flat_set<T> &o) const {
        if (count() != o.count()) {
            return false;
        }

        flat_set<T, A> a(*this), b(o);

        std::sort(a.begin(), a.end());
        std::sort(b.begin(), b.end());

        return a.vec == b.vec;
    }

    template<class T, class Allocator>
    void flat_set<T, Allocator>::insert(std::initializer_list<T> ilist) {
        for(auto& e : ilist) {
            insert(e);
        }
    }
}

#endif //CHIMERIC_FLAT_SET_H
