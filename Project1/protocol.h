#pragma once
#include <SDL.h>
#include <vector>
class Protocol
{
private:
	Uint32 code;
	//std::vector<std::pair<int, std::pair<SDL_Rect*, int*>>> eventsCleanQueue;
public:
	Protocol(Uint32 code) {
		SDL_Log("Protocol initialized \n");
		this->code = code;
	}

	Protocol() {
		SDL_Log("Protocol closed \n");
	}

	void send(SDL_Rect* attack, int* damage);
	bool listen(SDL_Event *e, SDL_Rect& interact, int& damage);
	void clean();
};

// player1 100
// player1 mirror 101

