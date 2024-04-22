#pragma once
#include "timer.h"
#include <map>
#include <vector>

class TimerManager {
private:
    static std::map<int, Timer*> timers;

public:
    static Timer* getTimer(int id);

    static Timer* createTimer(int id, Uint32 duration);

    static void destroyTimer(int id);

    static void updateAllTimers();
};

