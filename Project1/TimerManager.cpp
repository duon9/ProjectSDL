#include "TimerManager.h"

Timer* TimerManager::getTimer(int id) {
    if (timers.find(id) != timers.end()) {
        return timers[id];
    }
    return nullptr;
}

Timer* TimerManager::createTimer(int id, Uint32 duration) {
    Timer* timer = new Timer(duration);
    timers[id] = timer;
    return timer;
}

void TimerManager::destroyTimer(int id) {
    if (timers.find(id) != timers.end()) {
        delete timers[id];
        timers.erase(id);
    }
}

void TimerManager::updateAllTimers() {
    std::vector<int> expiredTimers;

    for (auto& pair : timers) {
        pair.second->update();
        if (pair.second->isExpired()) {
            expiredTimers.push_back(pair.first);
        }
    }

    for (int id : expiredTimers) {
        destroyTimer(id);
    }
}