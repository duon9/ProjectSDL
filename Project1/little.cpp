#include "little.h"

SDL_Texture* Little::vessel = nullptr;

void Little::draw() {
	SDL_RenderCopyEx(renderer, Little::vessel, &srcRect, &desRect, NULL, NULL, flip);
}