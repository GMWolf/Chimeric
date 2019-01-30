//
// Created by felix on 18/12/2018.
//

#include <chrono>
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

    //update all systems
    auto start = std::chrono::high_resolution_clock::now();
    for(size_t i = 0; i < systems.size(); i++) {
        systems[i]->update();
        //get system time
        const auto end = std::chrono::high_resolution_clock::now();
        systemTime[i] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        start = end;
    }

    //subscriptions dirty bits
    dynamic_bitset dirty;
    for(auto cm : componentManagers) {
        if (subscriptionsByBit.size() > cm->bit) {
            if (cm->batchAdd.any() || cm->batchRemove.any()) {
                dirty = cm->batchAdd;
                dirty |= cm->batchRemove;
                for (auto sub : subscriptionsByBit[cm->bit]) {
                    sub->dirtyEntities |= dirty;
                }
            }
        }

        cm->processBatchTasks(*this);
    }

    //update subscriptions
    for(auto& s : subscriptions) {
       s->update();
    }

    entities.update();

    const auto end = std::chrono::high_resolution_clock::now();
    ECStime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
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

chimeric::FamilySubscription& chimeric::World::getSubscription(const chimeric::Family &family) {

    auto s = std::make_unique<FamilySubscription>(*this, family);

    dynamic_bitset allbits = s->bitsets.all;
    allbits |= s->bitsets.exlcude;
    allbits |= s->bitsets.one;

    allbits.foreachset([&](auto e) {
        if (subscriptionsByBit.size() <= e) {
            subscriptionsByBit.resize(e + 1);
        }
        subscriptionsByBit[e].insert(s.get());
    });

    subscriptions.push_back(std::move(s));
    return *subscriptions.back();
}

size_t chimeric::World::systemCount() {
    return systems.size();
}

float chimeric::World::getSystemTime(size_t i) {
    return systemTime[i];
}

float chimeric::World::getECStime() {
    return ECStime;
}
