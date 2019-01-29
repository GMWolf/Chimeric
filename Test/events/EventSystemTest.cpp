
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
}