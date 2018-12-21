//
// Created by felix on 18/12/2018.
//

#ifndef CHIMERIC_WORLD_H
#define CHIMERIC_WORLD_H

#include "ResourceManager.h"

namespace chimeric {

    class World {
        ResourceManager resources;
        std::unordered_map<std::type_index, size_t> componentIDs;

    public:
        template<class T>
        size_t getComponentID();
    };



    template<class T>
    size_t World::getComponentID() {
        return componentIDs[typeid(T)];
    }

}

#endif //CHIMERIC_WORLD_H
