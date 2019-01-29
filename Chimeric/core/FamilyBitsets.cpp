
//
// Created by Felix Bridault on 29/01/2019.
//

#include "FamilyBitsets.h"
#include "World.h"

chimeric::FamilyBitsets::FamilyBitsets(const World &world, const Family &family) {

    for(auto c : family.all_set) {
        all.set(world.getComponentID(c));
    }

    for(auto c : family.exclude_set) {
        exlcude.set(world.getComponentID(c));
    }

    for(auto c : family.one_set) {
        one.set(world.getComponentID(c));
    }

}

bool chimeric::FamilyBitsets::matches(const chimeric::dynamic_bitset &aspect) const{
    return aspect.containsAll(all)
           && (one.none() || aspect.intersects(one))
           && aspect.notIntersects(exlcude);
}
