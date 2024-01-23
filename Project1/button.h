#pragma once
#include <SDL.h>
#include <string>
#include <SDL_ttf.h>
#include <iostream>
#include <SDL_image.h>

class Button
{
private:
	SDL_Rect buttonRect;
	SDL_Renderer* renderer;
	TTF_Font* font;
	std::string text;
	int x, y, w, h;
	SDL_Texture* buttonTextTexture = nullptr;
	SDL_Surface* buttonTextSurface = nullptr;

public:
	Button(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y, int w, int h);
	~Button();
	void render();
	void renderText();
	bool handleUserActions(SDL_Event& e);
	void init();
};
