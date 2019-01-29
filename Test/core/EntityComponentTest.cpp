//
// Created by felix on 21/12/2018.
//

#include "../catch.hpp"
#include "common.h"
#include "core/World.h"

using namespace chimeric;

struct ComponentA {
    int a, b, c;
    ComponentA(int a, int b, int c) : a(a), b(b), c(c) {
    };
    bool operator==(const ComponentA& o) const {
        return (a == o.a) && (b == o.b) && (c == o.c);
    };
};


TEST_CASE("Entity Component Store") {

    SECTION("Store and retrieve", "[CS]") {
        World world;

        world.registerComponent<ComponentA>();
/*
        auto& mapperA = world.get<ComponentManager<ComponentA>>();

        auto e1 = world.create();
        auto e2 = world.create();

        REQUIRE_FALSE(mapperA.has(e1));
        REQUIRE_FALSE(mapperA.has(e2));

        mapperA.emplace(e1, 1, 2, 3);
        REQUIRE(mapperA.has(e1));
        REQUIRE_FALSE(mapperA.has(e2));
        mapperA.emplace(e2, 3, 1, 4);
        REQUIRE(mapperA.has(e1));
        REQUIRE(mapperA.has(e2));

        REQUIRE(mapperA[e1] == ComponentA(1,2,3));
        REQUIRE(mapperA[e2] == ComponentA(3,1,4));
        */
    }

    SECTION("Remove and destruct", "[CS]") {
        World world;

        world.registerComponent<destructorTest>();

        auto& mapper = world.get<ComponentManager<destructorTest>>();

        bool destructed = false;

        auto e = world.create();

        mapper.emplace(e, destructed);

        REQUIRE(mapper.has(e));

        mapper.remove(e);

        REQUIRE_FALSE(mapper.has(e));
        REQUIRE(mapper.available(e));

        world.update();

        REQUIRE(destructed);
        REQUIRE_FALSE(mapper.available(e));
    }

    SECTION("Entity destroy", "[CS]") {

        bool destructed = false;


        World world;

        world.registerComponent<destructorTest>();

        auto& mapper = world.get<ComponentManager<destructorTest>>();

        auto e = world.create();

        mapper.emplace(e, destructed);

        REQUIRE(mapper.has(e));

        world.destroy(e);

        REQUIRE_FALSE(mapper.has(e));
        REQUIRE(mapper.available(e));

        world.update();

        REQUIRE_FALSE(mapper.available(e));

        REQUIRE(destructed);
    }

    SECTION("World destruct", "[CS]") {

        bool destructed = false;

        {
            World world;

            world.registerComponent<destructorTest>();

            auto& mapper = world.get<ComponentManager<destructorTest>>();

            auto e = world.create();

            mapper.emplace(e, destructed);
        }

        REQUIRE(destructed);

    }

}