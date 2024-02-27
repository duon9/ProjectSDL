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

	//eventsCleanQueue.push_back(std::make_pair(code, std::make_pair(static_cast<SDL_Rect*>(message.user.data1), static_cast<int*>(message.user.data2))));
}

bool Protocol::listen(SDL_Event* e, SDL_Rect& interact, int& damage) {
	if (e->type == SDL_USEREVENT) {
		//std::cout << "listen found signal" << std::endl;
		if (e->user.code != Protocol::code) {
			interact = *(static_cast<SDL_Rect*>(e->user.data1));
			damage = *(static_cast<int*>(e->user.data2));
			return true;
		}
		if (e->user.code == Protocol::code) {
			return false;
		}
	}
	return false;
}

//void Protocol::clean() {
//	if (!eventsCleanQueue.empty()) {
//		for (auto it = eventsCleanQueue.begin(); it != eventsCleanQueue.end(); it++) {
//			if (it->first == code) {
//				delete it->second.first;
//				delete it->second.second;
//			}
//			eventsCleanQueue.erase(it);
//		}
//	}
//}