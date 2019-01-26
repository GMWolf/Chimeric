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

        using iterator = std::vector<size_t>::const_iterator;

        const World& world;
        dynamic_bitset all;
        dynamic_bitset exlcude;
        dynamic_bitset one;


        dynamic_bitset entitiesActive;


        dynamic_bitset dirtyEntities;

    public:
        std::vector<size_t> entities;

        FamilySubscription(const World& world, const Family& family);

        iterator begin() const;
        iterator end() const;

        void update();

        bool match(size_t e) const;
    };
}


#endif //CHIMERIC_FAMILYSUBSCRIPTION_H
