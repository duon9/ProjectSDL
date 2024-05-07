#pragma once
#include "animated_button.h"
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
	AnimatedButton* fps60 = nullptr;
	AnimatedButton* fps90 = nullptr;
	SDL_Renderer* renderer = nullptr;
	TTF_Font* fbutton = nullptr;
	SDL_Rect object;
	SDL_Rect button;
	TTF_Font* font = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Texture* text1 = nullptr;
	SDL_Texture* text2 = nullptr;
	SDL_Texture* fps = nullptr;
	SDL_Rect fpsdes = { 100, 45, 0, 0 };
};

