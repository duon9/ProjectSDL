#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <iostream>
#include "menu.h"
#include "interface.h"
#include "entity.h"
#include "constant.h"
#include "player.h"
#include "computer.h"
#include "EntityManager.h"
#include "FPScontroller.h"

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
	SDL_Event e;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	int screenWidth;
	int screenHeight;
	void handleEvents();
	void gameLoop();
	void render();
	Map* map = new Map;


	Menu* menu = nullptr;
	GameState gamestate;
	Interface* interface = nullptr;
	//Player* player1 = nullptr;
	EntityManager* entitys = nullptr;
};
