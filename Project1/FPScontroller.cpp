#include "FPScontroller.h"

void FPScontroller::FPSlimit(int frameRate) {
    static Uint32 lastTime = SDL_GetTicks();
    Uint32 currentTime, elapsedTime;

    // Get current time
    currentTime = SDL_GetTicks();

    // Calculate time elapsed since last frame
    elapsedTime = currentTime - lastTime;

    // Delay if frame rate is too fast
    if (elapsedTime < 1000 / frameRate) {
        SDL_Delay((1000 / frameRate) - elapsedTime);
    }

    // Update last time
    lastTime = currentTime;
}

float FPScontroller::getFPS() {
    static Uint32 lastTime = SDL_GetTicks();
    static int frames = 0;
    Uint32 currentTime;
    float fps;

    // Get current time
    currentTime = SDL_GetTicks();

    // Calculate elapsed time since last frame
    Uint32 elapsedTime = currentTime - lastTime;

    // Increase frame count
    frames++;

    // Update FPS every 1 second (1000 milliseconds)

    fps = frames / (elapsedTime / 1000.0f);

    // Reset frame count and update last time
    frames = 0;
    lastTime = currentTime;

    // Return current FPS
    return fps;

}