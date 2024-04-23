#include <SDL.h>

#pragma once

class Timer {
private:
    Uint32 startTime;
    Uint32 elapsedTime;
    Uint32 duration;

public:
    Timer(Uint32 duration) : startTime(0), elapsedTime(0), duration(duration) {}

    void start();

    Uint32 getElapsedTime() const;

    Uint32 getDuration() const;

    void update();

    bool isExpired() const;

    void reset(Uint32 duration);
};

