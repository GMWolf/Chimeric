
//
// Created by Felix Bridault on 29/01/2019.
//

#ifndef CHIMERIC_FAMILYBITSETS_H
#define CHIMERIC_FAMILYBITSETS_H

#include "util/dynamic_bitset.h"
#include "Family.h"

namespace chimeric {

    class World;
    struct FamilyBitsets {
        dynamic_bitset all;
        dynamic_bitset exlcude;
        dynamic_bitset one;

        FamilyBitsets(const World& world, const Family& family);

        bool matches(const dynamic_bitset& aspect) const;
    };

}
#endif //CHIMERIC_FAMILYBITSETS_H
