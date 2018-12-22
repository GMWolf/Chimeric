//
// Created by felix on 22/12/2018.
//

#include "catch.hpp"
#include "common.h"
#include "core/World.h"
#include "core/FamilySubscription.h"
#include "core/Family.h"

using namespace chimeric;

struct ComponentA {
    int a;
};

struct ComponentB{
    int a;
};

struct ComponentC {
    int a;
};

TEST_CASE("Family subscriptions") {

    SECTION("Math All", "[FS]") {

        World world;
        world.registerComponent<ComponentA>();
        world.registerComponent<ComponentB>();
        world.registerComponent<ComponentC>();

        auto& mapperA = world.get<ComponentManager<ComponentA>>();
        auto& mapperB = world.get<ComponentManager<ComponentB>>();
        auto& mapperC = world.get<ComponentManager<ComponentC>>();

        FamilySubscription s(world, Family().all<ComponentA, ComponentB, ComponentC>());

        auto e = world.create();

        mapperA.emplace(e);

        REQUIRE_FALSE(s.match(e));

        mapperB.emplace(e);

        REQUIRE_FALSE(s.match(e));

        mapperC.emplace(e);

        REQUIRE(s.match(e));
        //REQUIRE(world.entities.getAspect(e)[2]);
    }

}