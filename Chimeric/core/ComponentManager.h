//
// Created by felix on 19/12/2018.
//

#ifndef CHIMERIC_COMPONENTSTORE_H
#define CHIMERIC_COMPONENTSTORE_H

#include "store/HashedArrayTree.h"
#include "storage.h"

namespace chimeric {

    template<class T>
    class ComponentManager {

        Store<T> store;
    };

}

#endif //CHIMERIC_COMPONENTSTORE_H
