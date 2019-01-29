//
// Created by felix on 22/12/2018.
//

#include "FamilySubscription.h"
#include "World.h"
#include "Family.h"

chimeric::FamilySubscription::FamilySubscription(const chimeric::World &world, const chimeric::Family &family) :
    world(world),
    bitsets(world, family) {

}

bool chimeric::FamilySubscription::match(size_t e) const{

    auto& aspect = world.entities.getAspect(e);

    return bitsets.matches(aspect);
}

chimeric::FamilySubscription::iterator chimeric::FamilySubscription::begin() const{
    return entities.begin();
}

chimeric::FamilySubscription::iterator chimeric::FamilySubscription::end() const{
    return entities.end();
}

void chimeric::FamilySubscription::update() {

    if (dirtyEntities.any()) {

        //Update active set
        dirtyEntities.foreachset([&](auto e) {
            entitiesActive.set(e, match(e));
        });
        dirtyEntities.reset();

        //update vector
        entities.clear();
        entitiesActive.foreachset([&](auto e) {
            entities.push_back(e);
        });

    }
}
