#include "protocol.h"
#include <iostream>

void Protocol::send(SDL_Rect* interact, int* damage) {
	SDL_Event message;
	message.type = SDL_USEREVENT;
	message.user.timestamp = SDL_GetTicks();
	message.user.windowID = 0;
	message.user.code = Protocol::code;
	message.user.data1 = static_cast<void*>(new SDL_Rect(*interact));
	message.user.data2 = static_cast<void*>(new int(*damage));

	SDL_PushEvent(&message);
}

void Protocol::listen(SDL_Event* e, SDL_Rect** interact, int** damage) {
	if (e->type == SDL_USEREVENT) {
		//std::cout << "listen found signal" << std::endl;
		if (e->user.code == Protocol::code) {
			return;
		}
		else {
			std::cout << "found enemy signal" << std::endl;
			*interact = static_cast<SDL_Rect*>(e->user.data1);
			*damage = static_cast<int*>(e->user.data2);
		}
	}
}