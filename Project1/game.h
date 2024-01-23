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

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	int screenWidth;
	int screenHeight;
	void handleEvents();
	void gameLoop();
	void render();
	Menu* menu = nullptr;
	GameState gamestate;
	Interface* interface = nullptr;
	Entity* human = nullptr;
};
