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
bool global::isHaveArcane = true;
std::vector<SDL_Rect*> global::lighthouse;
SDL_Rect global::lightRect = { 0,0,360,360 };
std::unordered_map<std::string, SDL_Texture*> global::resources;
std::unordered_map<std::string, std::vector<Frame>*> global::frames;
std::unordered_map<std::string, Stat*> global::stats;
std::unordered_map<std::string, std::vector<std::vector<SDL_Rect>>*> global::clips;
std::vector<damageTile*> global::dtiles;
std::vector<Entity*> global::layers;
//std::vector<std::vector<int>> global::collider;