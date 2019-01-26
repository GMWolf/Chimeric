//
// Created by felix on 19/12/2018.
//
#include <cstring>
#include "catch.hpp"
#include "core/Component.h"

using namespace chimeric;


struct A {
    int a;
};

template<> struct chimeric::Component<A> {
    using store = HashedArrayTree<A, 16>;
    static constexpr const char* name = "A";
};


struct B {
    int b;
};

template<> struct chimeric::Component<B> {
    using store = HashedArrayTree<B, 32>;
    static constexpr const char* name = "B";
};


TEST_CASE("Component Traits") {

    SECTION("Store Type", "[CT]") {
        CHECK(std::is_same<Store<A>, HashedArrayTree<A, 16>>::value);
        CHECK(std::is_same<Store<B>, HashedArrayTree<B, 32>>::value);
    }

    SECTION("Name", "[CT}") {
        CHECK(std::strcmp(chimeric::Component<A>::name, "A") == 0);
        CHECK(std::strcmp(chimeric::Component<B>::name, "B") == 0);
    }


}
