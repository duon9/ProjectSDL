#pragma once
#include "npc.h"
#include "dialogue_box.h"

class Guard : public NPC
{
private:

public:
	Guard(SDL_Renderer* renderer, std::string type = "npc_guard") : NPC(renderer, type) {
		texture = TextureManagement::LoadTexture("assets/characters/captain.png", renderer);
	}

	~Guard() {

	}
};

