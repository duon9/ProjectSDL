#pragma once
#include "npc.h"
class Obelisk : public NPC
{
private:
	//SDL_Rect* lumi = nullptr;
public:
	Obelisk(SDL_Renderer* renderer, std::string type = "obelisk") : NPC(renderer, type) {
		//texture = TextureManagement::LoadTexture("assets/characters/captain.png", renderer);
		dialogue.push_back("lorem ipsum luv verese nah ul hallab no");
		dialogue.push_back("solon nah ruj du ladd ipsum ilim");
		dialogue.push_back("solenium lissand liptob du vernia");
		
	}

	~Obelisk() {

	}
};

