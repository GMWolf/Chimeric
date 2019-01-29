//
// Created by felix on 21/12/2018.
//

#include "../catch.hpp"
#include "core/util/flat_set.h"
#include "common.h"

using namespace chimeric;

TEST_CASE("flat_set") {

    SECTION("insert", "[FS}") {

        flat_set<int> set;

        auto r = set.insert(5);

        REQUIRE(r.second);
        REQUIRE(*r.first == 5);
        REQUIRE(set.contains(5));

        REQUIRE_FALSE(set.contains(67));

        set.insert(67);

        REQUIRE(set.contains(67));
    }


    SECTION("erase", "[FS]") {

        flat_set<int> set;

        auto numbers = {0,4,5,87,124};

        for(int e : numbers) {
            set.insert(e);
        }

        set.insert(42);

        for(int e : numbers) {
            REQUIRE(set.contains(e));
        }
        REQUIRE(set.contains(42));


        set.erase(set.find(42));

        REQUIRE_FALSE(set.contains(42));

        for(int e : numbers) {

            REQUIRE(set.contains(e));
        }

    }


    SECTION("equals", "[FS]") {
        flat_set a{1,4,9,6,2};
        flat_set b{2,4,6,9,1};

        REQUIRE(a == b);
    }

}