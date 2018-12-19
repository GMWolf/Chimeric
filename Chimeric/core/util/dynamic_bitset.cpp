//
// Created by felix on 19/12/2018.
//

#include "dynamic_bitset.h"

chimeric::dynamic_bitset::dynamic_bitset(chimeric::dynamic_bitset &&o) noexcept : words(std::move(o.words))  {
}

chimeric::dynamic_bitset::dynamic_bitset(const chimeric::dynamic_bitset &o) = default;


chimeric::dynamic_bitset::reference chimeric::dynamic_bitset::operator[](size_t i) {
    if (i >= words.size()){
        words.resize(i);
    }

    return words[i / wordSize][i % wordSize];
}

bool chimeric::dynamic_bitset::operator[](size_t i) const {
    return test(i);
}

bool chimeric::dynamic_bitset::test(size_t i) const {
    return (i < (words.size() * wordSize)) && words[i / wordSize][i % wordSize];
}

bool chimeric::dynamic_bitset::any() const {
    for(auto& w : words) {
        if (w.any()) {
            return true;
        }
    }
    return false;
}

bool chimeric::dynamic_bitset::none() const {
    for(auto& w : words) {
        if (w.any()) {
            return false;
        }
    }
    return true;
}

size_t chimeric::dynamic_bitset::count() const {
    size_t count = 0;
    for(auto& w : words) {
        count += w.count();
    }

    return count;
}

void chimeric::dynamic_bitset::set(size_t i) {
    const size_t w = i / wordSize;
    if (w >= words.size()) {
        words.resize(w+1);
    }
    words[w].set(i % wordSize);
}

void chimeric::dynamic_bitset::set(size_t i, bool value) {
    const size_t w = i / wordSize;
    if (w >= words.size()) {
        words.resize(w+1);
    }
    words[i / wordSize].set(i % wordSize, value);
}

void chimeric::dynamic_bitset::reset() {
    words.resize(0);
}

void chimeric::dynamic_bitset::reset(size_t i) {
    const size_t w = i / wordSize;
    if (w < words.size()) {
        words[w].reset(i % wordSize);
    }
}

void chimeric::dynamic_bitset::flip(size_t i) {
    const size_t w = i / wordSize;
    if (w >= words.size()) {
        words.resize(w+1);
    }
    words[i / wordSize].flip(i % wordSize);
}

chimeric::dynamic_bitset &chimeric::dynamic_bitset::operator&=(const chimeric::dynamic_bitset &o) {

    const size_t m = std::min(words.size(), o.words.size());
    for(size_t i = 0; i < m; i++) {
        words[i] &= o.words[i];
    }

    words.resize(m);

    return *this;
}

chimeric::dynamic_bitset &chimeric::dynamic_bitset::operator|=(const chimeric::dynamic_bitset &o) {

    const size_t m = std::min(words.size(), o.words.size());
    for(size_t i = 0; i < m; i++) {
        words[i] |= o.words[i];
    }

    if (words.size() < o.words.size()) {
        words.resize(o.words.size());
        for (size_t i = m; i < o.words.size(); i++) {
            words[i] = o.words[i];
        }
    }

    return *this;
}

chimeric::dynamic_bitset &chimeric::dynamic_bitset::operator^=(const chimeric::dynamic_bitset &o) {

    const size_t m = std::min(words.size(), o.words.size());
    for(size_t i = 0; i < m; i++) {
        words[i] ^= o.words[i];
    }

    if (words.size() < o.words.size()) {
        words.resize(o.words.size());
        for(size_t i = m; i < o.words.size(); i++) {
            words[i] = o.words[i];
        }
    } else {
        const auto zero = std::bitset<wordSize>();
        for(size_t i = m; i < words.size(); i++) {
            words[i] ^= zero;
        }
    }

    return *this;
}

chimeric::dynamic_bitset &chimeric::dynamic_bitset::operator=(chimeric::dynamic_bitset &&o) noexcept {
    words.swap(o.words);
    return *this;
}

chimeric::dynamic_bitset &chimeric::dynamic_bitset::operator=(const chimeric::dynamic_bitset &o) {
    words = o.words;
    return *this;
}

bool chimeric::dynamic_bitset::operator==(const chimeric::dynamic_bitset &o) const {
    return words == o.words;
}

bool chimeric::dynamic_bitset::operator!=(const chimeric::dynamic_bitset &o) const {
    return words != o.words;
}

chimeric::dynamic_bitset chimeric::dynamic_bitset::operator&(const chimeric::dynamic_bitset &o) const {
    return dynamic_bitset(*this) &= o;
}

chimeric::dynamic_bitset chimeric::dynamic_bitset::operator|(const chimeric::dynamic_bitset &o) const {
    return chimeric::dynamic_bitset(*this) |= o;
}

chimeric::dynamic_bitset chimeric::dynamic_bitset::operator^(const chimeric::dynamic_bitset &o) const {
    return chimeric::dynamic_bitset(*this) ^= o;
}

bool chimeric::dynamic_bitset::containsAll(const chimeric::dynamic_bitset &o) const {
    size_t m = std::min(words.size(), o.words.size());

    for(size_t i = m; i < o.words.size(); i++) {
        if (o.words[i].any()) {
            return false;
        }
    }

    for(size_t i = 0; i < m; i++) {
        if ((words[i] & o.words[i]) != o.words[i]) {
            return false;
        }
    }

    return true;
}

bool chimeric::dynamic_bitset::subsetOf(const chimeric::dynamic_bitset &o) const {
    return o.containsAll(*this);
}

void chimeric::dynamic_bitset::swap(chimeric::dynamic_bitset &o) {
    std::swap(words, o.words);
}

std::ostream &chimeric::operator<<(std::ostream &os, const chimeric::dynamic_bitset &bitset) {
    for(int i = static_cast<int>(bitset.words.size() - 1); i >= 0; i--) {
        os << bitset.words[i];
    }
    return os;
}

