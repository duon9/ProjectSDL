#pragma once
#include "timer.h"
#include <map>
#include <vector>

class TimerManager {
private:
    std::map<int, Timer*> timers;

public:
    Timer* getTimer(int id);

    Timer* createTimer(int id, Uint32 duration);

    void destroyTimer(int id);

    void updateAllTimers();
};

