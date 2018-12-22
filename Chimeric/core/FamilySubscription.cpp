//
// Created by felix on 22/12/2018.
//

#include "FamilySubscription.h"
#include "World.h"
#include "Family.h"

chimeric::FamilySubscription::FamilySubscription(const chimeric::World &world, const chimeric::Family &family) : world(world) {
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

bool chimeric::FamilySubscription::match(size_t e) {

    auto& aspect = world.entities.getAspect(e);

    return aspect.containsAll(all)
        && (one.none() || aspect.intersects(one))
        && aspect.notIntersects(exlcude);
}
