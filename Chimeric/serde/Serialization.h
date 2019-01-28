
//
// Created by Felix Bridault on 28/01/2019.
//

#ifndef CHIMERIC_SERIALIZATION_H
#define CHIMERIC_SERIALIZATION_H

#include <string>

namespace chimeric {

    template<class T, class C>
    struct Serde {
        static void deserialize (const T&, C&) {};
    };

    template<class U, class T>
    std::vector<std::pair<std::string, T>> getComponentSource(const U& s) {

    }

    template<class U>
    void load(World& world, const U& str) {

        //get json
        //do recursive stuff
        //for each object in json
        //for each title get component tuype
        //serd that object
        //yay
    }


}

#endif //CHIMERIC_SERIALIZATION_H
