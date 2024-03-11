#pragma once
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
	SDL_Rect interRect;
	SDL_Rect textRect;
	std::string content;
	SDL_Texture* text = nullptr;
	SDL_Texture* text1 = nullptr;
	SDL_Texture* text2 = nullptr;
	SDL_Color color1 = { 255, 255, 255, 255 };

public:
	AnimatedButton(SDL_Renderer* renderer, SDL_Rect object, std::string content, TTF_Font* font) {
		this->renderer = renderer;
		this->content = content;
		this->font = font;
		this->outerRect = object;
		innerRect = { outerRect.x + 2, outerRect.y + 2, outerRect.w - 4, outerRect.h - 4 };
		interRect = { innerRect.x + 1, innerRect.y + 1, innerRect.w - 2, innerRect.h - 2 };
	}

	~AnimatedButton() {
		SDL_DestroyTexture(text);
		SDL_DestroyTexture(text1);
		SDL_DestroyTexture(text2);
	}
	bool handleUserMouseMotion(SDL_Event& e);
	void init();
	void render();
};

