//
// Created by felix on 21/12/2018.
//

#ifndef CHIMERIC_ENTITYMANAGER_H
#define CHIMERIC_ENTITYMANAGER_H

#include <queue>
#include "util/dynamic_bitset.h"
#include "store/HashedArrayTree.h"

namespace chimeric {

    class EntityManager {
        HashedArrayTree<dynamic_bitset, 256> compositionVectors;
        std::queue<size_t> entityIDQueue;
        size_t nextEntityID = 0;
    public:
        size_t create();
        void destroy(size_t id);
    };

}


#endif //CHIMERIC_ENTITYMANAGER_H
