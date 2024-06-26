#pragma once
#include "player.h"
#include "constant.h"
#include "minotaur.h"
#include "little.h"
#include "NightBorne.h"
#include "skeleton.h"
#include "npc_guard.h"
#include "FireWorm.h"
#include "portal.h"
#include "MaceSkeleton.h"
#include "obelisk.h"
#include "wizard.h"
#include "receptionist.h"
#include "guidegirl.h"
#include "Wave.h"
#include "ResourceManager.h"

class EntityManager
{
private:
	SDL_Renderer* renderer = nullptr;
	SDL_Event* e = nullptr;
	std::vector<std::vector<int>> collider;
	Player* player = nullptr;
	std::vector<Computer*> computers;
	std::vector<NPC*> npcs;
	Interface* interface = nullptr;
	Map map = GREYYARD;
	ResourceManager& manager = ResourceManager::getInstance();
	QuestManager& quest = QuestManager::getInstance();
	
public:

	EntityManager(SDL_Renderer* renderer, SDL_Event* e, Map* map, Interface* interface);
	~EntityManager();
	void save();
	void load();
	void init();
	void render();
	void HandleEvents();
	void sortLayer();
	bool isInScreen(SDL_Rect object1, SDL_Rect object2);
	void reload();
	void clean();
	void setComputer();
	void setMapLogic();
};

