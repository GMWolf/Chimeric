//
// Created by felix on 21/12/2018.
//

#ifndef CHIMERIC_ASPECT_H
#define CHIMERIC_ASPECT_H

#include "util/dynamic_bitset.h"
#include "World.h"

namespace chimeric {

    class Family {

    public:

        template<class... C>
        Family all();

        template<class... C>
        Family one();

        template<class... C>
        Family exclude();
    };


}

#endif //CHIMERIC_ASPECT_H
