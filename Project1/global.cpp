#include "global.h"
#include <SDL.h>

std::vector<Missle*> global::missles;
std::vector<Teleporter*> global::teleporters;
SDL_Renderer* global::renderer = nullptr;
SDL_Window* global::window = nullptr;
SDL_Event global::e;