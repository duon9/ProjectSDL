#pragma once
#include "npc.h"

class Receptionist : public NPC
{
private:
	//SDL_Rect* lumi = nullptr;
public:
	Receptionist(SDL_Renderer* renderer, std::string type = "receptionist") : NPC(renderer, type) {
		//texture = TextureManagement::LoadTexture("assets/characters/captain.png", renderer);
		dialogue.push_back("welcome to pearl harbor guidance");
		dialogue.push_back("you look too young to become to a adventurer");
		dialogue.push_back("however, due current event, we still allow you");
		dialogue.push_back("you will start with Porcelain rank \n each mission you finish");
		dialogue.push_back("we will assess to uprank for you");
		dialogue.push_back("now go to the QuestGiver to take your first quest");
		dialogue.push_back("good luck kid");
	}

	~Receptionist() {

	}
};

