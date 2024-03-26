#pragma once
#include <iostream>
#include <SDL_ttf.h>
#include "utils.h"

class Header
{
public:
	Header(SDL_Renderer* renderer, std::string content, TTF_Font* font) {
		this->renderer = renderer;
		this->content = content;
		this->font = font;
	}
	~Header() {
		SDL_DestroyTexture(texture);
	}
	void init();
	void render();
	void setRectPosition();
private:
	SDL_Renderer* renderer = nullptr;
	std::string content;
	TTF_Font* font = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Rect textRect;
	SDL_Color color = { 255,255,255,255 };
};

