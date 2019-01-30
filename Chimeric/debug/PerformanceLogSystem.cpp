
//
// Created by Felix Bridault on 30/01/2019.
//

#include "PerformanceLogSystem.h"
#include "../core/World.h"

void chimeric::PerformanceLogSystem::update() {

    if (systemTimeLogs.size() < world.systemCount()) {
        systemTimeLogs.resize(world.systemCount());
    }

    for(size_t i = 0; i < world.systemCount(); i++) {
        logSystem(i);
    }

    ECStimeLog.push_back(world.getECStime());
    if (ECStimeLog.size() > plotSize) {
        systemTimeLogs.pop_back();
    }

}

void chimeric::PerformanceLogSystem::logSystem(size_t systemIndex) {

    systemTimeLogs[systemIndex].push_back(world.getSystemTime(systemIndex));
    if (systemTimeLogs[systemIndex].size() > plotSize) {
        systemTimeLogs[systemIndex].pop_front();
    }

}

const std::deque<float> &chimeric::PerformanceLogSystem::getSystemPlot(size_t systemIndex) {
    return systemTimeLogs[systemIndex];
}

const std::deque<float> &chimeric::PerformanceLogSystem::getECStimeLog() {
    return ECStimeLog;
}
