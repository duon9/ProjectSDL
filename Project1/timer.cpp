#include "timer.h"

void Timer::start() {
    startTime = SDL_GetTicks();
}

Uint32 Timer::getElapsedTime() const {
    return elapsedTime;
}

Uint32 Timer::getDuration() const {
    return duration;
}

void Timer::update() {
    elapsedTime = SDL_GetTicks() - startTime;
}

bool Timer::isExpired() const {
    return elapsedTime >= duration;
}

void Timer::reset(Uint32 duration) {
    start();
    this->duration = duration;
}