#pragma once
#include "player.h"
#include "constant.h"
#include "minotaur.h"
#include "little.h"
#include "NightBorne.h"
#include "skeleton.h"

class EntityManager
{
private:
	SDL_Renderer* renderer = nullptr;
	SDL_Event* e = nullptr;
	std::vector<std::vector<int>> collider;
	Player* player = nullptr;
	std::vector<Computer*> computers;
	std::vector<Entity*> layers;
	Interface* interface = nullptr;
	Map map = GREYYARD;
	
public:

	EntityManager(SDL_Renderer* renderer, SDL_Event* e, Map* map, Interface* interface);
	~EntityManager();

	void init();
	void render();
	void HandleEvents();
	void sortLayer();
	bool isInScreen(SDL_Rect object1, SDL_Rect object2);
	void reload();
	void clean();
	void setComputer();
};

