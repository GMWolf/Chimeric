//
// Created by felix on 27/01/2019.
//


#include "catch.hpp"
#include "common.h"
#include "core/World.h"
#include "core/System.h"

using namespace chimeric;




TEST_CASE("System") {

    SECTION("Add and update", "[Sys]") {

        class incSystem : public System {
        public:
            int& a;
            incSystem(World &world, int& a) : a(a), System(world) {
            }

            void update() override {
                a++;
            }
        };

        World world;

        int n = 0;
        world.addSystem<incSystem>(n);

        for(int i = 0; i < 10; i++) {
            REQUIRE(n == i);
            world.update();
        }

    }
}
