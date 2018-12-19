//
// Created by felix on 19/12/2018.
//

#include "catch.hpp"
#include "core/util/dynamic_bitset.h"
#include "common.h"

using namespace chimeric;


TEST_CASE("Dynamic bitset") {

    using bitset = dynamic_bitset;

    SECTION("Set and test") {

        bitset bs;

        bs.set(6);
        bs.set(9);
        bs.set(45);
        bs.set(75);
        bs.set(80);
        bs.set(156);

        REQUIRE(bs.test(6));
        REQUIRE(bs.test(9));
        REQUIRE(bs.test(45));
        REQUIRE(bs.test(75));
        REQUIRE(bs.test(80));
        REQUIRE(bs.test(156));


        REQUIRE_FALSE(bs.test(0));
        REQUIRE_FALSE(bs.test(7));
        REQUIRE_FALSE(bs.test(46));
        REQUIRE_FALSE(bs.test(90));
        REQUIRE_FALSE(bs.test(160));
    }




}