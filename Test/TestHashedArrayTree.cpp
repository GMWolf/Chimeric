//
// Created by felix on 19/12/2018.
//

#include <iostream>
#include "catch.hpp"
#include "core/store/HashedArrayTree.h"
#include "common.h"

using namespace chimeric;


TEST_CASE("HashedArrayTree") {

    SECTION("Add and retrieve", "[HAT]") {

        HashedArrayTree<int> hat;

        hat.emplace(0, 6);

        REQUIRE(hat[0] == 6);

        hat.emplace(63, 5);

        REQUIRE(hat[63] == 5);

        hat.emplace(24, 43);

        REQUIRE(hat[24] == 43);


        hat.emplace(67, 8);

        REQUIRE(hat[67] == 8);
    }

    SECTION("Add and has", "[HAT]") {

        HashedArrayTree<char> hat;

        hat.emplace(6, 8);
        REQUIRE(hat.has(6));

        hat.emplace(145, 65);
        REQUIRE(hat.has(145));

    }

    SECTION("Does not have empty", "[HAT]") {

        HashedArrayTree<int> hat;

        REQUIRE_FALSE(hat.has(4));
        hat.emplace(4, 56);
        REQUIRE(hat.has(4));


        REQUIRE_FALSE(hat.has(145));
        hat.emplace(145, 7);
        REQUIRE(hat.has(145));
    }


    SECTION("Destructors called") {

        bool destructed[8]{};

        for(int i = 0; i < 8; i++) REQUIRE_FALSE(destructed[i]);

        {
            HashedArrayTree<destructorTest, 8> hat;

            for(int i = 0; i < 8; i++) {
                hat.emplace(i * 7, destructed[i]);
            }

            for(int i = 0; i < 8; i++) {
                hat.erase(i * 7);
                REQUIRE(destructed[i]);
            }
        }



    }

    SECTION("Destructors called on destruct") {

        bool destructed[8]{};

        for(int i = 0; i < 8; i++) REQUIRE_FALSE(destructed[i]);

        {
            HashedArrayTree<destructorTest, 8> hat;

            for(int i = 0; i < 8; i++) {
                hat.emplace(i * 7, destructed[i]);
            }
        }

        for(int i = 0; i < 8; i++) REQUIRE(destructed[i]);
    }

}