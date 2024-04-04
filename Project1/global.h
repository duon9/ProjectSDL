#pragma once
#include "Missle.h"
#include "teleporter.h"
#include <vector>

namespace global {
	extern std::vector<Missle*> missles;
	extern std::vector<Teleporter*> teleporters;
	extern SDL_Renderer* renderer;
	extern SDL_Window* window;
	extern SDL_Event e;
}



