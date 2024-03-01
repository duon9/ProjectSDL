#include "label.h"

void Label::init() {
	font = TTF_OpenFont("assets/fonts/test.ttf", 1);
	if (font == nullptr) std::cerr << "Failed to load font" << std::endl;
}

void Label::render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(renderer, &desRect);
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_RenderCopy(renderer, texture, NULL, &desRect);
	SDL_FreeSurface(surface);
}