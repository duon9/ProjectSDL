#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>
#include <string>
#include <iostream>
#include "button.h"

class Menu
{
public:
	Menu(SDL_Renderer* renderer);
	~Menu();
	void init();
	void render();
	int handleMenuEvents(SDL_Event& e);
private:
	Button* newGame = nullptr;
	Button* loadGame = nullptr;
	std::vector<Button> menuButton;
	TTF_Font* menuFont = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Surface* menuSurface = nullptr;
	SDL_Texture* menuTexture = nullptr;
};
