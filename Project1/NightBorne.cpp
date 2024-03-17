#include "NightBorne.h"

SDL_Texture* NightBorne::vessel = nullptr;

void NightBorne::draw() {
	SDL_RenderCopyEx(renderer, NightBorne::vessel, &srcRect, &desRect, NULL, NULL, flip);
}

void NightBorne::death() {
	if (timer >= 230) return;
	timer++;

	if (timer <= 180 && timer >= 130) {
		
		SDL_Rect rect = getRect();
		int damage = stat.damage * 10;
		protocol->send(&rect, &damage);
	}
	/*SDL_Rect rect = getRect();
	int damage = stat.damage * 100;
	protocol->send(&rect, &damage);*/
}
