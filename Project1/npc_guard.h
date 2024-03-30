#pragma once
#include "npc.h"

class Guard : public NPC
{
public:
	Guard(SDL_Renderer* renderer, std::string type = "npc_guard") : NPC(renderer, type) {
		texture = TextureManagement::LoadTexture("assets/characters/captain.png", renderer);
	}

	~Guard() {

	}
};

