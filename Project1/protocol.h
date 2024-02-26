#pragma once
#include <SDL.h>

class Protocol
{
private:
	Uint32 code;
public:
	Protocol(Uint32 code) {
		SDL_Log("Protocol initialized \n");
		this->code = code;
	}

	Protocol() {
		SDL_Log("Protocol closed \n");
	}

	void send(SDL_Rect* attack, int* damage);
	void listen(SDL_Event *e, SDL_Rect **interact, int** damage);
};

// player1 100
// player1 mirror 101

