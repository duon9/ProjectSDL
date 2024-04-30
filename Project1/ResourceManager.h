#pragma once
#include "SDL.h"
#include <vector>
#include <iostream>
#include <SDL_thread.h>
class ResourceManager
{
private:
	SDL_Thread* thread1 = nullptr;
	ResourceManager() {}
public:

	static ResourceManager& getInstance() {
		static ResourceManager instance;
		return instance;
	}

	int loadNPCProperties(void*data);
	void run();
	void wait();
};

