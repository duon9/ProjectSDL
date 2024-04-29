#pragma once
#include "npc.h"
class GuideGirl : public NPC
{
private:
	//SDL_Rect* lumi = nullptr;
public:
	GuideGirl(SDL_Renderer* renderer, std::string type = "questgiver") : NPC(renderer, type) {
		//texture = TextureManagement::LoadTexture("assets/characters/captain.png", renderer);
		dialogue.push_back("no mission at the moment");
	}

	~GuideGirl() {

	}
};

