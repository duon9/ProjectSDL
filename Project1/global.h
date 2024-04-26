#pragma once
#include "Missle.h"
#include "teleporter.h"
#include "damageTile.h"
#include <vector>
#include <unordered_map>

namespace global {
	extern std::vector<Entity*> layers;
	extern std::vector<damageTile*> dtiles;
	extern std::vector<Missle*> missles;
	extern std::vector<Teleporter*> teleporters;
	extern SDL_Renderer* renderer;
	extern SDL_Window* window;
	extern SDL_Event e;
	extern bool isPause;
	extern bool isEscape;
	extern bool isDark;
	extern bool isHaveArcane;
	extern SDL_Rect lightRect;
	extern std::vector<SDL_Rect*> lighthouse;
	extern std::unordered_map<std::string, SDL_Texture*> resources;
	extern std::unordered_map<std::string, std::vector<Frame>*> frames;
	extern std::unordered_map<std::string, Stat*> stats;
	extern std::unordered_map<std::string, std::vector<std::vector<SDL_Rect>>*> clips;
}



