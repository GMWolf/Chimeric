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
    for(auto& cm : componentManagers) {

        //Get dirty bits


        cm->processBatchTasks(*this);
    }

    entities.update();
}

size_t chimeric::World::getComponentID(std::type_index c) const{
    return componentIDs.at(c);
}

chimeric::World::World() {
    resources.emplace<AspectStore>();
}

chimeric::baseComponentManager *chimeric::World::getComponentManager(const char *name) {
    auto id = componentIdByName[name];
    return componentManagersByID[id];
}

chimeric::FamilySubscription &chimeric::World::getSubscription(const chimeric::Family &family) {

    auto s = std::make_unique<FamilySubscription>(*this, family);
    subscriptions.push_back(std::move(s));

    return *subscriptions.back();
}

