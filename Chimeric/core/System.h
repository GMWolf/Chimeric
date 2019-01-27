//
// Created by felix on 27/01/2019.
//

#ifndef CHIMERIC_SYSTEM_H
#define CHIMERIC_SYSTEM_H

namespace chimeric {

    class World;
    class System {
    protected:
        World& world;
    public:
        System(const System&) = delete;
        System& operator=(const System&) = delete;

        System(World& world);

        virtual ~System();

        virtual void update() = 0;
    };


}
#endif //CHIMERIC_SYSTEM_H
