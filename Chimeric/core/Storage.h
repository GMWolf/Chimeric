//
// Created by felix on 19/12/2018.
//

#ifndef CHIMERIC_STORAGE_H
#define CHIMERIC_STORAGE_H

#include "store/HashedArrayTree.h"

namespace chimeric {

    template<class T>
    struct StoreType {
        using type = HashedArrayTree<T, 64>;
    };

    template <class T> using Store = typename StoreType<T>::type;

}

#endif //CHIMERIC_STORAGE_H
