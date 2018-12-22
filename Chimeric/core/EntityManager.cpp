//
// Created by felix on 21/12/2018.
//

#include "EntityManager.h"

size_t chimeric::EntityManager::create() {

    size_t id;
    if (entityIDQueue.empty()) {
        id = nextEntityID++;
    } else {
        id = entityIDQueue.front();
        entityIDQueue.pop();
    }

    compositionVectors.emplace(id);

    return id;
}

void chimeric::EntityManager::destroy(size_t id) {
    //entityIDQueue.push(id);
    //compositionVectors.erase(id);
    purgatory.insert(id);
}

chimeric::dynamic_bitset &chimeric::EntityManager::getAspect(size_t id) {
    return compositionVectors[id];
}

const chimeric::dynamic_bitset &chimeric::EntityManager::getAspect(size_t id) const {
    return compositionVectors[id];
}

void chimeric::EntityManager::update() {
    for(auto e : purgatory) {
        entityIDQueue.push(e);
        compositionVectors.erase(e);
    }

    purgatory.clear();
}
