#pragma once
#include "npc.h"
#include "dialogue_box.h"
#include "global.h"

class Guard : public NPC
{
private:
	SDL_Rect* lumi = nullptr;
public:
	Guard(SDL_Renderer* renderer, std::string type = "npc_guard") : NPC(renderer, type) {
		texture = TextureManagement::LoadTexture("assets/characters/captain.png", renderer);
		dialogue.push_back("lorem ipsum luv verese nah ul hallab no");
		dialogue.push_back("solon nah ruj du ladd ipsum ilim");
		dialogue.push_back("solenium lissand liptob du vernia");
		lumi = new SDL_Rect();
		lumi->w = 360;
		lumi->h = 360;
		lumi->x = desRect.x + desRect.w / 2 - lumi->w / 2;
		lumi->y = desRect.y + desRect.h / 2 - lumi->h / 2;
		global::lighthouse.push_back(lumi);
	}

	~Guard() {
	
	}
	virtual void update() override;
};

