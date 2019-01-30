//
// Created by felix on 27/01/2019.
//


#include <debug/PerformanceLogSystem.h>
#include "../catch.hpp"
#include "common.h"
#include "core/World.h"
#include "core/System.h"
#include "core/Family.h"

using namespace chimeric;


struct Position {
    float x,y,z;
};

struct Velocity {
    float x,y,z;
};

struct Acceleration {
    float x,y,z;
};

class velSystem : public System{
public:

    FamilySubscription& entities;
    ComponentManager<Velocity>& velocities;
    ComponentManager<Position>& positions;


    explicit velSystem(World &world) :
        System(world),
        entities(world.getSubscription(Family().all<Position, Velocity>())),
        positions(world.get<ComponentManager<Position>>()),
        velocities(world.get<ComponentManager<Velocity>>()){
    }

    void update() override {
        for(auto e : entities) {
            positions[e].x += velocities[e].x;
            positions[e].y += velocities[e].y;
            positions[e].z += velocities[e].z;
        }
    }

};

class accSystem : public System{
public:
    FamilySubscription& entities;
    ComponentManager<Velocity>& velocities;
    ComponentManager<Acceleration>& accelerations;
    explicit accSystem(World &world) :
        System(world),
        entities(world.getSubscription(Family().all<Velocity, Acceleration>())),
        velocities(world.get<ComponentManager<Velocity>>()),
        accelerations(world.get<ComponentManager<Acceleration>>()){
    }

    void update() override {
        for(auto e : entities) {
            velocities[e].x += accelerations[e].x;
            velocities[e].y += accelerations[e].y;
            velocities[e].z += accelerations[e].z;
        }
    }
};

TEST_CASE("Full") {

    SECTION("part", "[full]") {

        const size_t entityCount = 128;

        //Setup ECS
        World world;
        world.registerComponent<Position>();
        world.registerComponent<Velocity>();
        world.registerComponent<Acceleration>();

        world.addSystem<accSystem>();
        world.addSystem<velSystem>();
        world.addSystem<PerformanceLogSystem>();

        ComponentManager<Position>& posMapper = world.get<ComponentManager<Position>>();
        ComponentManager<Velocity>& velMapper = world.get<ComponentManager<Velocity>>();
        ComponentManager<Acceleration>& accMapper = world.get<ComponentManager<Acceleration>>();

        //setup control data
        Acceleration acc[entityCount];
        Velocity vel[entityCount];
        Position pos[entityCount];


        //Create entities & control data
        for(size_t i = 0; i < entityCount; i++) {

            auto e = world.create();
            acc[i].x = rand() / (float)RAND_MAX;
            acc[i].y = rand() / (float)RAND_MAX;
            acc[i].z = rand() / (float)RAND_MAX;
            vel[i].x = rand() / (float)RAND_MAX;
            vel[i].y = rand() / (float)RAND_MAX;
            vel[i].z = rand() / (float)RAND_MAX;
            pos[i].x = rand() / (float)RAND_MAX;
            pos[i].y = rand() / (float)RAND_MAX;
            pos[i].z = rand() / (float)RAND_MAX;

            posMapper.emplace(e, pos[i]);
            velMapper.emplace(e, vel[i]);
            accMapper.emplace(e, acc[i]);
        }

        //Update world to prime subscriptions
        world.update();


        //update loop
        for(int i = 0; i < 100; i ++) {
            //update world
            world.update();

            //update control data
            for(auto e = 0; e < entityCount; e++) {
                vel[e].x += acc[e].x;
                vel[e].y += acc[e].y;
                vel[e].z += acc[e].z;
                pos[e].x += vel[e].x;
                pos[e].y += vel[e].y;
                pos[e].z += vel[e].z;

                REQUIRE(posMapper[e].x == pos[e].x);
                REQUIRE(posMapper[e].y == pos[e].y);
                REQUIRE(posMapper[e].z == pos[e].z);
            }
        }

    }
}