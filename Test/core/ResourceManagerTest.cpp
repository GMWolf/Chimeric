//
// Created by felix on 18/12/2018.
//

#include <iostream>
#include "../catch.hpp"
#include "core/ResourceManager.h"
#include "common.h"

using namespace chimeric;

TEST_CASE("Resource Manager") {

    SECTION("Resource Manager can store and retreive", "[RM]") {

        ResourceManager rm;

        rm.emplace<std::string>("Yo");

        rm.emplace<int>(5);

        REQUIRE(rm.get<std::string>() == "Yo");
        REQUIRE(rm.get<int>() == 5);
    }

    SECTION("Resource Manager can delete objects", "[RM]") {

        bool destructed = false;

        {
            ResourceManager  rm;
            rm.emplace<destructorTest>(destructed);
        }

        REQUIRE(destructed);
    }

}