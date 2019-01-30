//
// Created by felix on 19/12/2018.
//

#include "dynamic_bitset.h"
#include <utility>
#include <string>
#include <algorithm>

chimeric::dynamic_bitset::dynamic_bitset(chimeric::dynamic_bitset &&o) noexcept : words(std::move(o.words))  {
}

chimeric::dynamic_bitset::dynamic_bitset(const chimeric::dynamic_bitset &o) = default;

chimeric::dynamic_bitset::dynamic_bitset(const std::string &string) {
    size_t n = ((string.length() + wordSize - 1) / wordSize);
    words.resize(n);

    for(int i = 0; i < n; i++) {
        size_t a = string.length() - (i * wordSize);
        size_t b = (size_t) std::max(0, ((int)a) - ((int)wordSize));
        size_t l = a - b;
        words[i] = word(string, b, l);
    }
}

chimeric::dynamic_bitset::dynamic_bitset(std::initializer_list<size_t> il) {
    for(size_t e : il) {
        set(e);
    }
}

chimeric::dynamic_bitset::reference chimeric::dynamic_bitset::operator[](size_t i) {
    const size_t w = i / wordSize;
    if (w >= words.size()) {
        words.resize(w+1);
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
        const auto zero = word();
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

chimeric::dynamic_bitset &chimeric::dynamic_bitset::operator=(const chimeric::dynamic_bitset &o) = default;

bool chimeric::dynamic_bitset::operator==(const chimeric::dynamic_bitset &o) const {
    size_t m = std::min(words.size(), o.words.size());

    for(size_t i = m; i < words.size(); i++) {
        if (words[i].any()) {
            return false;
        }
    }

    for(size_t i = m; i < o.words.size(); i++) {
        if (o.words[i].any()) {
            return false;
        }
    }

    for(size_t i = 0; i < m; i++) {
        if (words[i] != o.words[i]) {
            return false;
        }
    }

    return true;
}

bool chimeric::dynamic_bitset::operator!=(const chimeric::dynamic_bitset &o) const {
    size_t m = std::min(words.size(), o.words.size());

    for(size_t i = m; i < words.size(); i++) {
        if (words[i].any()) {
            return true;
        }
    }

    for(size_t i = m; i < o.words.size(); i++) {
        if (o.words[i].any()) {
            return true;
        }
    }

    for(size_t i = 0; i < m; i++) {
        if (words[i] != o.words[i]) {
            return true;
        }
    }

    return false;
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

bool chimeric::dynamic_bitset::intersects(const chimeric::dynamic_bitset &o) const {
    size_t m = std::min(words.size(), o.words.size());

    for(size_t i = 0; i < m; i++) {
        if ((words[i] & o.words[i]).any()) {
            return true;
        }
    }

    return false;
}

bool chimeric::dynamic_bitset::notIntersects(const chimeric::dynamic_bitset &o) const {
    size_t m = std::min(words.size(), o.words.size());

    for(size_t i = 0; i < m; i++) {
        if((words[i] & o.words[i]).any()) {
            return false;
        }
    }

    return true;
}



void chimeric::dynamic_bitset::swap(chimeric::dynamic_bitset &o) {
    std::swap(words, o.words);
}

std::ostream &chimeric::operator<<(std::ostream &os, const chimeric::dynamic_bitset &bitset) {
    for(auto i = static_cast<int>(bitset.words.size() - 1); i >= 0; i--) {
        os << bitset.words[i];
    }
    return os;
}

void chimeric::dynamic_bitset::trim() {
    size_t i = words.size();
    while(words[i - 1].none() && i > 0) i--;
    words.resize(i);
}

std::vector<size_t> chimeric::dynamic_bitset::toIntVector() {
    std::vector<size_t> vector;

    foreachset([&](size_t e){
       vector.push_back(e);
    });

    return vector;
}





