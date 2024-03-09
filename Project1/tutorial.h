#pragma once

#include "utils.h"

class Tutorial
{
public:
	Tutorial(SDL_Renderer* renderer, TTF_Font* font) {
		this->renderer = renderer;
		this->font = font;
	}
	~Tutorial() {

	}
	void init();
	void render();
	bool handleEvents(SDL_Event e);
	void test();

private:
	SDL_Renderer* renderer = nullptr;
	SDL_Rect object;
	SDL_Rect button;
	TTF_Font* font = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Texture* text1 = nullptr;
	SDL_Texture* text2 = nullptr;

};

