//
// Created by felix on 19/12/2018.
//

#ifndef CHIMERIC_STORAGE_H
#define CHIMERIC_STORAGE_H

#include "store/HashedArrayTree.h"

namespace chimeric {

    template<class T>
    struct Component {
        using store = HashedArrayTree<T, 64>;
        static constexpr const char* name = "No Name";
        static constexpr auto loader = [](T& o){};
    };

    template <class T> using Store = typename Component<T>::store;

}

#endif //CHIMERIC_STORAGE_H
