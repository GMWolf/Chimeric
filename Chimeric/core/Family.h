//
// Created by felix on 21/12/2018.
//

#ifndef CHIMERIC_ASPECT_H
#define CHIMERIC_ASPECT_H

#include "util/flat_set.h"
#include "World.h"

namespace chimeric {

    class Family {
        friend class FamilySubscription;
        flat_set<std::type_index> all_set;
        flat_set<std::type_index> one_set;
        flat_set<std::type_index> exclude_set;

    public:
        template<class... C>
        Family& all();

        template<class... C>
        Family& one();

        template<class... C>
        Family& exclude();
    };


    template<class... C>
    Family& Family::all() {
        all_set.insert({typeid(C)...});
        return *this;
    }

    template<class... C>
    Family& Family::one() {
        one_set.insert({typeid(C)...});
        return *this;
    }

    template<class... C>
    Family& Family::exclude() {
        exclude_set.insert({typeid(C)...});
        return *this;
    }


}

#endif //CHIMERIC_ASPECT_H
