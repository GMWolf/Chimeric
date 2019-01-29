//
// Created by felix on 19/12/2018.
//

#ifndef CHIMERIC_COMMON_H
#define CHIMERIC_COMMON_H

struct destructorTest {
    bool& d;

    explicit destructorTest(bool& d) : d(d) {
    }

    ~destructorTest(){
        d  = true;
    }
};

#endif //CHIMERIC_COMMON_H
