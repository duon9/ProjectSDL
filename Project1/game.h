#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

enum GameState {PLAY, EXIT};

class Game
{
public:
	Game();
	~Game();
	void run();

private:
	void init(const char* title, int _x, int _y, int w, int h, Uint32 flags);

	void gameLoop();

	void handleEvents();

	SDL_Window* window;
	SDL_Renderer* renderer;
	int screenWidth;
	int screenHeight;

	GameState gamestate;
};

