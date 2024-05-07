#pragma once
#include "ResourceManager.h"
#include "menu.h"
#include "interface.h"
#include "entity.h"
#include "constant.h"
#include "EntityManager.h"
#include "FPScontroller.h"
#include "utils.h"
#include "global.h"

class Game
{
public:
	//constructor & destructor
	//TO DO:
	Game();
	~Game();
	void run();

private:
	void init(const char* title, int _x, int _y, int w, int h, Uint32 flags);
	int screenWidth;
	int screenHeight;
	void handleEvents();
	void gameLoop();
	void render();
	Map* map = new Map;

	ResourceManager& manager = ResourceManager::getInstance();
	Menu* menu = nullptr;
	Interface* interface = nullptr;
	//Player* player1 = nullptr;
	EntityManager* entitys = nullptr;
};

