#include "button.h"

#include <iostream>

Button::Button(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, int x, int y, int w, int h) : renderer(renderer), font(font), text(text), x(x), y(y), w(w), h(h) {
	std::cout << "Constructor button started" << std::endl;
}

Button::~Button() {
	/*
	* free resource
	*/

	SDL_FreeSurface(buttonTextSurface);
	SDL_DestroyTexture(buttonTextTexture);
	//SDL_DestroyRenderer(renderer);
	//TTF_CloseFont(font);
}

void Button::init() {
	/*
	* initialize text surface
	*/

	buttonTextSurface = TTF_RenderText_Solid(font, text.c_str(), { 0, 0, 0, 255 });
	buttonTextTexture = SDL_CreateTextureFromSurface(renderer, buttonTextSurface);
	buttonRect = { x, y, w, h };
	//std::cout << "buttonrect" << buttonRect.x << ' ' << buttonRect.w << std::endl;
}

void Button::render() {
	// std::cout << "start render button" << std::endl;

	//buttonRect = { x, y, w, h };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderFillRect(renderer, &buttonRect);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &buttonRect);

	renderText();
}

void Button::renderText() {
	SDL_Rect textRect = { x + w / 2 - buttonTextSurface->w / 2, y + h / 2, buttonTextSurface->w, buttonTextSurface->h };
	SDL_RenderCopy(renderer, buttonTextTexture, nullptr, &textRect);
}

bool Button::handleUserActions(SDL_Event& e) {
	SDL_Point currPos = { e.motion.x, e.motion.y };
	if (SDL_PointInRect(&currPos, &buttonRect)) {
		if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
			std::cout << "button with name of: " << text << " clicked" << std::endl;
			return 1;
		}
	}
	return 0;
}