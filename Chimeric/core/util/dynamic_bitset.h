//
// Created by felix on 19/12/2018.
//

#ifndef CHIMERIC_DYNAMIC_BITSET_H
#define CHIMERIC_DYNAMIC_BITSET_H

#include <vector>
#include <bitset>
#include <ostream>

namespace chimeric {

    class dynamic_bitset{
        static const size_t wordSize = 64;
        std::vector<std::bitset<wordSize>> words;
    public:
        using reference = typename std::bitset<wordSize>::reference;

        dynamic_bitset() = default;
        dynamic_bitset(dynamic_bitset&& o) noexcept;
        dynamic_bitset(const dynamic_bitset& o);

        void swap(dynamic_bitset& o);

        dynamic_bitset& operator=(dynamic_bitset&& o) noexcept;
        dynamic_bitset& operator=(const dynamic_bitset& o);

        reference operator[](size_t i);
        bool operator[](size_t i) const;

        bool test(size_t i) const;
        bool any() const;
        bool none() const;
        size_t count() const;

        void set(size_t i);
        void set(size_t i, bool value);
        void reset();
        void reset(size_t i);
        void flip(size_t i);

        dynamic_bitset& operator&=(const dynamic_bitset& o);
        dynamic_bitset& operator|=(const dynamic_bitset& o);
        dynamic_bitset& operator^=(const dynamic_bitset& o);

        dynamic_bitset operator&(const dynamic_bitset& o) const;
        dynamic_bitset operator|(const dynamic_bitset& o) const;
        dynamic_bitset operator^(const dynamic_bitset& o) const;

        bool operator==(const dynamic_bitset& o) const;
        bool operator!=(const dynamic_bitset& o) const;

        bool containsAll(const dynamic_bitset& o) const;
        bool subsetOf(const dynamic_bitset& o) const;

        friend std::ostream &operator<<(std::ostream &os, const dynamic_bitset &bitset);
    };

}


#endif //CHIMERIC_DYNAMIC_BITSET_H
