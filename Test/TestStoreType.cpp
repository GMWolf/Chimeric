//
// Created by felix on 19/12/2018.
//

#include "catch.hpp"
#include "core/Storage.h"

using namespace chimeric;


struct a {
    int a;
};

struct b {
    int b;
};

template<> struct chimeric::StoreType<a> { using type = HashedArrayTree<a, 16>;};
template<> struct chimeric::StoreType<b> { using type = HashedArrayTree<b, 32>;};


TEST_CASE("Component Store Type") {

    SECTION("Type", "[CST]") {
        REQUIRE(std::is_same<Store<a>, HashedArrayTree<a, 16>>::value);
        REQUIRE(std::is_same<Store<b>, HashedArrayTree<b, 32>>::value);
    }

}
