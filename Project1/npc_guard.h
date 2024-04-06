#pragma once
#include "npc.h"
#include "dialogue_box.h"

class Guard : public NPC
{
private:

public:
	Guard(SDL_Renderer* renderer, std::string type = "npc_guard") : NPC(renderer, type) {
		texture = TextureManagement::LoadTexture("assets/characters/captain.png", renderer);
		dialogue.push_back("lorem ipsum luv verese nah ul hallab no");
		dialogue.push_back("solon nah ruj du ladd ipsum ilim");
		dialogue.push_back("solenium lissand liptob du vernia");
	}

	~Guard() {

	}
};

