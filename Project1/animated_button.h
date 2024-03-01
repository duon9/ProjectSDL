#pragma once
#include "label.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "utils.h"


class AnimatedButton
{
private:
	SDL_Renderer* renderer = nullptr;
	TTF_Font* font = nullptr;
	SDL_Rect outerRect;
	SDL_Rect innerRect;
	SDL_Rect textRect;
	std::string content;
	SDL_Texture* text = nullptr;

public:
	AnimatedButton(SDL_Renderer* renderer, SDL_Rect object, std::string content, TTF_Font* font) {
		this->renderer = renderer;
		this->content = content;
		this->font = font;
		this->outerRect = object;
	}
	void handleUserMouseMotion(SDL_Event& e);
	void init();
};

