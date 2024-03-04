#include "header.h"

void Header::init() {
	texture = TextureManagement::LoadText(renderer, font, content, color);
	SDL_QueryTexture(texture, NULL, NULL, &textRect.w, &textRect.h);
	setRectPosition();
}

void Header::setRectPosition() {
	textRect.x = SCREEN_WIDTH / 2 - textRect.w / 2;
	textRect.y = 45;
}

void Header::render() {
	SDL_RenderCopy(renderer, texture, NULL, &textRect);
}