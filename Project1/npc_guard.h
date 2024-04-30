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
		//dialogue.clear();
		dialogue.push_back("welcome to pearl harbor");
		dialogue.push_back("come to the receptionist to take the mission");
		dialogue.push_back("good luck kid");
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

