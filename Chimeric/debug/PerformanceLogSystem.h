
//
// Created by Felix Bridault on 30/01/2019.
//

#ifndef CHIMERIC_PERFORMANCELOGSYSTEM_H
#define CHIMERIC_PERFORMANCELOGSYSTEM_H

#include "../core/System.h"
#include <vector>
#include <deque>

namespace chimeric {

    class PerformanceLogSystem : public System {
        std::vector<std::deque<float>> systemTimeLogs;
        std::deque<float> ECStimeLog;
    public:
        PerformanceLogSystem(World& world) : System(world){};
        const size_t plotSize = 120;
        void update() override;

        const std::deque<float>& getSystemPlot(size_t systemIndex);

        const std::deque<float>& getECStimeLog();

    private:
        void logSystem(size_t systemIndex);

    };

}


#endif //CHIMERIC_PERFORMANCELOGSYSTEM_H
