//
// Created by felix on 19/12/2018.
//

#include "ComponentManager.h"
#include "World.h"


chimeric::baseComponentManager::baseComponentManager(chimeric::World &world, std::type_index c)
        : bit(world.getComponentID(c)) {
}

void chimeric::baseComponentManager::remove(size_t id) {
    batchRemove.set(id);
    batchAdd.reset(id);
}

void chimeric::baseComponentManager::processBatchTasks(chimeric::World &world) {

    batchRemove.foreachset([&](auto id) {
        world.entities.getAspect(id).reset(bit);
    });

    batchAdd.foreachset([&](auto id) {
       world.entities.getAspect(id).set(bit);
    });

    processBatchRemove();

    batchRemove.reset();
    batchAdd.reset();
}
