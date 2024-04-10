#include "global.h"
#include <SDL.h>

std::vector<Missle*> global::missles;
std::vector<Teleporter*> global::teleporters;
SDL_Renderer* global::renderer = nullptr;
SDL_Window* global::window = nullptr;
SDL_Event global::e;
bool global::isPause = false;
bool global::isEscape = false;
bool global::isDark = false;
std::vector<SDL_Rect*> global::lighthouse;
SDL_Rect global::lightRect = { 0,0,360,360 };