#include "skeleton.h"
SDL_Texture* Skeleton::vessel = nullptr;

void Skeleton::draw() {
	SDL_RenderCopyEx(renderer, Skeleton::vessel, &srcRect, &desRect, NULL, NULL, flip);
}