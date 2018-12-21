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
    entityIDQueue.push(id);
    compositionVectors.erase(id);
}
