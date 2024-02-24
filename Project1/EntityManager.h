#pragma once
#include <vector>
#include "player.h"
#include "computer.h"
#include "utils.h"
#include "constant.h"
#include "collision.h"

class EntityManager
{
private:
	SDL_Renderer* renderer = nullptr;
	SDL_Event* e = nullptr;
	SDL_Event interaction;
	std::vector<std::vector<int>> collider;
	std::vector<Player*> players;
	std::vector<Computer*> computers;
	Map* map = nullptr;
	Interface* interface = nullptr;
	
public:

	EntityManager(SDL_Renderer* renderer, SDL_Event* e, Map* map, Interface* interface);
	~EntityManager();

	void init();
	void render();
	void setCollision();
	void handleUserInput();
	void handleInteraction();
	void HandleEvents();

	bool isInScreen(SDL_Rect object1, SDL_Rect object2);
};
