//
// Created by felix on 21/12/2018.
//

#ifndef CHIMERIC_ENTITYMANAGER_H
#define CHIMERIC_ENTITYMANAGER_H

#include <queue>
#include "util/dynamic_bitset.h"
#include "store/HashedArrayTree.h"
#include "util/flat_set.h"

namespace chimeric {

    class EntityManager {
        HashedArrayTree<dynamic_bitset, 256> compositionVectors;
        std::queue<size_t> entityIDQueue;
        flat_set<size_t> purgatory;

        size_t nextEntityID = 0;
    public:
        size_t create();
        void destroy(size_t id);

        void update();

        dynamic_bitset& getAspect(size_t id);

        const dynamic_bitset& getAspect(size_t id) const;

    };

}


#endif //CHIMERIC_ENTITYMANAGER_H
