//
// Created by felix on 18/12/2018.
//

#include "World.h"
#include "ComponentManager.h"


size_t chimeric::World::create() {
    return entities.create();
}

void chimeric::World::destroy(size_t id) {
    entities.destroy(id);
    for(auto& m : componentManagers) {
        m->remove(id);
    }
}

void chimeric::World::update() {
    for(auto&& cm : componentManagers) {
        cm->processBatchTasks();
    }

    entities.update();
}

size_t chimeric::World::getComponentID(std::type_index c) const{
    return componentIDs.at(c);
}

