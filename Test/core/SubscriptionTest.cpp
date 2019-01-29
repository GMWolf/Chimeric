//
// Created by felix on 22/12/2018.
//

#include "../catch.hpp"
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

    SECTION("Match All", "[FS]") {

        World world;
        world.registerComponent<ComponentA>();
        world.registerComponent<ComponentB>();
        world.registerComponent<ComponentC>();

        auto& mapperA = world.get<ComponentManager<ComponentA>>();
        auto& mapperB = world.get<ComponentManager<ComponentB>>();
        auto& mapperC = world.get<ComponentManager<ComponentC>>();

        auto& s = world.getSubscription(Family().all<ComponentA, ComponentB, ComponentC>()) ;

        auto e = world.create();

        mapperA.emplace(e);
        world.update();
        REQUIRE_FALSE(s.match(e));

        mapperB.emplace(e);
        world.update();
        REQUIRE_FALSE(s.match(e));

        mapperC.emplace(e);
        world.update();
        REQUIRE(s.match(e));
    }

    SECTION("Match One", "[FS]") {

        World world;
        world.registerComponent<ComponentA>();
        world.registerComponent<ComponentB>();
        world.registerComponent<ComponentC>();

        auto& mapperA = world.get<ComponentManager<ComponentA>>();
        auto& mapperB = world.get<ComponentManager<ComponentB>>();
        auto& mapperC = world.get<ComponentManager<ComponentC>>();

        auto& s = world.getSubscription(Family().one<ComponentA, ComponentB, ComponentC>()) ;

        auto e1 = world.create();
        auto e2 = world.create();
        auto e3 = world.create();

        mapperA.emplace(e1);
        world.update();
        REQUIRE(s.match(e1));
        REQUIRE_FALSE(s.match(e2));
        REQUIRE_FALSE(s.match(e3));

        mapperB.emplace(e1);
        mapperB.emplace(e2);
        world.update();
        REQUIRE(s.match(e1));
        REQUIRE(s.match(e2));
        REQUIRE_FALSE(s.match(e3));

        mapperC.emplace(e1);
        mapperC.emplace(e2);
        mapperC.emplace(e3);
        world.update();
        REQUIRE(s.match(e1));
        REQUIRE(s.match(e2));
        REQUIRE(s.match(e3));

    }


    SECTION("Match exclude", "[FS]") {
        World world;
        world.registerComponent<ComponentA>();
        world.registerComponent<ComponentB>();
        world.registerComponent<ComponentC>();

        auto& mapperA = world.get<ComponentManager<ComponentA>>();
        auto& mapperB = world.get<ComponentManager<ComponentB>>();
        auto& mapperC = world.get<ComponentManager<ComponentC>>();

        auto& s = world.getSubscription(Family().all<ComponentA>().exclude<ComponentB, ComponentC>()) ;

        auto e1 = world.create();
        auto e2 = world.create();

        mapperA.emplace(e1);
        mapperA.emplace(e2);
        world.update();
        REQUIRE(s.match(e1));
        REQUIRE(s.match(e2));

        mapperB.emplace(e1);
        mapperC.emplace(e2);
        world.update();
        REQUIRE_FALSE(s.match(e1));
        REQUIRE_FALSE(s.match(e2));
    }


    SECTION("Subscription list", "[FS]") {

        World world;
        world.registerComponent<ComponentA>();
        world.registerComponent<ComponentB>();
        world.registerComponent<ComponentC>();

        auto& mapperA = world.get<ComponentManager<ComponentA>>();
        auto& mapperB = world.get<ComponentManager<ComponentB>>();
        auto& mapperC = world.get<ComponentManager<ComponentC>>();

        auto& s = world.getSubscription(Family().all<ComponentA, ComponentB>().exclude<ComponentC>());

        auto e1 = world.create();
        auto e2 = world.create();
        auto e3 = world.create();

        REQUIRE(s.entities.empty());

        mapperA.emplace(e1);
        mapperB.emplace(e2);
        mapperC.emplace(e3);


        world.update();
        REQUIRE(s.entities.empty());

        mapperB.emplace(e1);
        mapperA.emplace(e2);
        mapperA.emplace(e3);
        mapperB.emplace(e3);


        world.update();
        REQUIRE(s.match(e1));
        REQUIRE(s.match(e2));

        REQUIRE(s.entities == std::vector{e1, e2});

        mapperA.remove(e1);
        mapperC.emplace(e2);
        mapperC.remove(e3);

        world.update();

        REQUIRE(s.entities == std::vector{e3});
    }

    SECTION("Subscription entity destroy") {
        World world;
        world.registerComponent<ComponentA>();
        world.registerComponent<ComponentB>();
        world.registerComponent<ComponentC>();

        auto& mapperA = world.get<ComponentManager<ComponentA>>();
        auto& mapperB = world.get<ComponentManager<ComponentB>>();
        auto& mapperC = world.get<ComponentManager<ComponentC>>();

        auto& s = world.getSubscription(Family().all<ComponentA, ComponentB, ComponentC>());

        std::vector es {
                world.create(),
                world.create(),
                world.create()
        };

        for(auto e : es) {
            mapperA.emplace(e);
            mapperB.emplace(e);
            mapperC.emplace(e);
        }

        world.update();

        REQUIRE(s.entities == es);

        for(auto e : es) {
            world.destroy(e);
            world.update();
            REQUIRE(std::find(s.entities.begin(), s.entities.end(), e) == s.entities.end());
        }
    }

}