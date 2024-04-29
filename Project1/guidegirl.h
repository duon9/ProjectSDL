#pragma once
#include "npc.h"
#include "QuestManager.h"

class GuideGirl : public NPC
{
private:
	//SDL_Rect* lumi = nullptr;
	Node* temp = nullptr;
	QuestManager manager = QuestManager::getInstance();
public:
	GuideGirl(SDL_Renderer* renderer, std::string type = "questgiver") : NPC(renderer, type) {
		//texture = TextureManagement::LoadTexture("assets/characters/captain.png", renderer);
		//dialogue.push_back("no mission at the moment");
		//manager = QuestManager::getInstance();
	}

	~GuideGirl() {

	}
	//void start();
	void resetDialogue();
	virtual void listen(SDL_Event* e) override;
};

