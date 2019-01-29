
//
// Created by Felix Bridault on 29/01/2019.
//


//
// Created by Felix Bridault on 29/01/2019.
//

#include "../catch.hpp"
#include "event/EventSystem.h"
#include "core/World.h"
using namespace chimeric;


struct TestEvent{
    int a; int b;
};

struct A {
    int a;
};

struct B {
    int b;
};

TEST_CASE("Event System") {


    SECTION("dispatch and queue", "[EV]") {

        World world;
        world.addSystem<EventSystem>();

        auto& es = world.get<EventSystem>();

        EventQueue<TestEvent> eq;

        es.registerQueue(eq);

        REQUIRE(eq.empty());

        es.dispatch(TestEvent{7,8});

        REQUIRE(eq.front().a == 7);
        REQUIRE(eq.front().b == 8);

        eq.pop();

        REQUIRE(eq.empty());

        es.dispatch(TestEvent{90, 78});
        es.dispatch(TestEvent{76, 45});

        REQUIRE(eq.front().a == 90);
        REQUIRE(eq.front().b == 78);
        eq.pop();
        REQUIRE(eq.front().a == 76);
        REQUIRE(eq.front().b == 45);
        eq.pop();

        REQUIRE(eq.empty());
    }


    SECTION("Entity Events", "[EV]"){


        World world;
        world.addSystem<EventSystem>();

        auto& es = world.get<EventSystem>();

        world.registerComponent<A>();
        world.registerComponent<B>();

        ComponentManager<A>& cma = world.get<ComponentManager<A>>();
        ComponentManager<B>& cmb = world.get<ComponentManager<B>>();

        EventQueue<TestEvent> eq1;
        EventQueue<TestEvent> eq2;

        es.registerQueue(eq1, Family().all<A>());
        es.registerQueue(eq2, Family().all<A, B>());

        auto e1 = world.create();
        auto e2 = world.create();

        cma.emplace(e1, A{1});

        cma.emplace(e2, A{2});
        cmb.emplace(e2, B{2});

        world.update();

        es.dispatch(TestEvent{1,1}, e1);
        es.dispatch(TestEvent{2,2}, e2);

        REQUIRE(!eq1.empty());
        REQUIRE(eq1.front().a == 1);
        eq1.pop();
        REQUIRE(eq1.front().a == 2);
        eq1.pop();
        REQUIRE(eq1.empty());

        REQUIRE(eq2.front().a == 2);
        eq2.pop();
        REQUIRE(eq2.empty());

    }
}