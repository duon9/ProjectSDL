#include "teleporter.h"

bool Teleporter::isTeleport(SDL_Rect object) {
	SDL_Rect i = getRect();
	if (SDL_HasIntersection(&object, &i)) {
		std::cout << "changing map" << std::endl;
	}
	return true;
}

void Teleporter::render() {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &desRect);
}

void Teleporter::init() {
	desRect.w = 100;
	desRect.h = 100;
	setLocation({ 300, 300 });
}