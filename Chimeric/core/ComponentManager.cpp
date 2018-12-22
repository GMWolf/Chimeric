//
// Created by felix on 19/12/2018.
//

#include "ComponentManager.h"
#include "World.h"

void chimeric::baseComponentManager::remove(size_t id) {
    batchRemove.insert(id);
    resetBit(id);
}

void chimeric::baseComponentManager::setBit(size_t e) {
    world.entities.getAspect(e).set(bit);
}

void chimeric::baseComponentManager::resetBit(size_t e) {
    world.entities.getAspect(e).reset(bit);
}

chimeric::baseComponentManager::baseComponentManager(chimeric::World &world, std::type_index c)
    : world(world), bit(world.getComponentID(c)) {}
