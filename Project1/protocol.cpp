#include "protocol.h"

void Protocol::send(SDL_Rect* interact, int* damage) {
	SDL_Event message;
	message.type = SDL_USEREVENT;
	message.user.timestamp = SDL_GetTicks();
	message.user.windowID = 0;
	message.user.code = Protocol::code;
	message.user.data1 = interact;
	message.user.data2 = damage;

	SDL_PushEvent(&message);
}

void Protocol::listen(SDL_Event* e, SDL_Rect* interact, int* damage) {
	if (e->type == SDL_USEREVENT) {
		if (e->user.code == Protocol::code) {
			return;
		}
		else {
			interact = (SDL_Rect*)e->user.data1;
			damage = (int*)e->user.data2;
		}
	}
}