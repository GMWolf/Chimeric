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
        using word = std::bitset<wordSize>;
        std::vector<word> words;
    public:
        using reference = typename std::bitset<wordSize>::reference;

        dynamic_bitset() = default;
        dynamic_bitset(dynamic_bitset&& o) noexcept;
        dynamic_bitset(const dynamic_bitset& o);

        explicit dynamic_bitset(const std::string& string);
        dynamic_bitset(std::initializer_list<size_t> il);

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
        bool intersects(const dynamic_bitset& o) const;
        bool notIntersects(const dynamic_bitset& o) const;

        void trim();

        std::vector<size_t> toIntVector();

        template<class L>
        void foreachset(L fun);
        template<class L>
        void foreachunset(L fun);

        friend std::ostream &operator<<(std::ostream &os, const dynamic_bitset &bitset);
    };

}


template<class L>
void chimeric::dynamic_bitset::foreachset(L fun) {
    size_t i = 0;
    for(auto& word : words) {
        if (word.any()) {
            for(size_t j = 0; j < wordSize; j++) {
                if (word[j]) {
                    fun(i + j);
                }
            }
        }
        i += wordSize;
    }
}

template<class L>
void chimeric::dynamic_bitset::foreachunset(L fun) {
    size_t i = 0;
    for(auto& word : words) {
        if (!word.all()) {
            for(size_t j = 0; j < wordSize; j++) {
                if (!word[j]) {
                    fun(i + j);
                }
            }
        }
        i += wordSize;
    }
}



#endif //CHIMERIC_DYNAMIC_BITSET_H
