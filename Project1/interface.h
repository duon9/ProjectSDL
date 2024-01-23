#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "utils.h"

class Interface {
private:

	SDL_Renderer* renderer;
	SDL_Rect src, dest;
	SDL_Texture* grass = nullptr;
	SDL_Texture* wooden = nullptr;
	SDL_Texture* lockdoor = nullptr;
	SDL_Texture* rock2 = nullptr;
	SDL_Texture* rock3 = nullptr;
	SDL_Texture* rock4 = nullptr;
	SDL_Texture* rock5 = nullptr;
	SDL_Texture* rock6 = nullptr;
	SDL_Texture* mini_chest_1 = nullptr;
	SDL_Texture* box1 = nullptr;
	SDL_Texture* flag_1 = nullptr;

	int map[38][50];

public:

	Interface(SDL_Renderer* renderer);
	~Interface();

	void init();
	void render();
	void load();
};