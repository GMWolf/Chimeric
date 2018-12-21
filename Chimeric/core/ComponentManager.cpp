//
// Created by felix on 19/12/2018.
//

#include "ComponentManager.h"

void chimeric::baseComponentManager::remove(size_t id) {
    batchRemove.insert(id);
}
