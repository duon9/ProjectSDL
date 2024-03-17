#include "NightBorne.h"

SDL_Texture* NightBorne::vessel = nullptr;

void NightBorne::draw() {
	SDL_RenderCopyEx(renderer, NightBorne::vessel, &srcRect, &desRect, NULL, NULL, flip);
}

void NightBorne::death() {
	SDL_Rect rect = getRect();
	int damage = stat.damage * 100;
	protocol->send(&rect, &damage);
}