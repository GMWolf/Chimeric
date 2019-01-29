//
// Created by felix on 19/12/2018.
//

#include <iostream>
#include "../catch.hpp"
#include "core/store/VecStore.h"
#include "common.h"

using namespace chimeric;

TEST_CASE("VecStore") {

    SECTION("Add and retrieve", "[Vec]") {

        VecStore<int> vec;

        vec.emplace(0, 6);

        REQUIRE(vec[0] == 6);

        vec.emplace(63, 5);

        REQUIRE(vec[63] == 5);

        vec.emplace(24, 43);

        REQUIRE(vec[24] == 43);

        vec.emplace(67, 8);

        REQUIRE(vec[67] == 8);
    }

    SECTION("Add and has", "[VEC]") {

        VecStore<char> vec;

        vec.emplace(6, 8);
        REQUIRE(vec.has(6));

        vec.emplace(145, 65);
        REQUIRE(vec.has(145));

    }

    SECTION("Does not have empty", "[VEC]") {

        VecStore<int> vec;

        REQUIRE_FALSE(vec.has(4));
        vec.emplace(4, 56);
        REQUIRE(vec.has(4));


        REQUIRE_FALSE(vec.has(145));
        vec.emplace(145, 7);
        REQUIRE(vec.has(145));
    }


    SECTION("Destructors called", "[VEC]") {

        bool destructed[8]{};

        for (bool i : destructed) REQUIRE_FALSE(i);

        {
            VecStore<destructorTest> vec;

            for(size_t i = 0; i < 8; i++) {
                vec.emplace(i * 7, destructed[i]);
            }

            for(size_t i = 0; i < 8; i++) {
                vec.erase(i * 7);
                REQUIRE(destructed[i]);
            }

        }



    }

    SECTION("Destructors called on destruct") {

        bool destructed[8]{};

        for (bool i : destructed) REQUIRE_FALSE(i);

        {
            VecStore<destructorTest> vec;

            for(size_t i = 0; i < 8; i++) {
                vec.emplace(i * 7, destructed[i]);
            }
        }

        for (bool i : destructed) REQUIRE(i);
    }

}