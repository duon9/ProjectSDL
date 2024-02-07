#pragma once
#include <vector>
#include "player.h"

struct Enemys {

};

class EntityManager
{
private:
	SDL_Renderer* renderer = nullptr;
	SDL_Event e;
	std::vector<std::vector<int>> collisionMap;
	std::vector<Player> playerManager;
	std::vector<Enemys> ememysManager;
	//std::vector<AnimatedTile> animatedTileManager;

public:

	EntityManager(SDL_Renderer* renderer, SDL_Event e);
	~EntityManager();

	void init();
	void render();
	void readCollision();
	void loadEntity();
};

