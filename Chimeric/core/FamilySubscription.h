//
// Created by felix on 22/12/2018.
//

#ifndef CHIMERIC_FAMILYSUBSCRIPTION_H
#define CHIMERIC_FAMILYSUBSCRIPTION_H

#include "util/dynamic_bitset.h"

namespace chimeric {

    class World;
    class Family;
    class FamilySubscription {
        friend class World;
        const World& world;
        dynamic_bitset all;
        dynamic_bitset exlcude;
        dynamic_bitset one;

        std::vector<size_t> entities;
        dynamic_bitset dirtyEntities;

    public:
        FamilySubscription(const World& world, const Family& family);

        bool match(size_t e);
    };
}


#endif //CHIMERIC_FAMILYSUBSCRIPTION_H
