#pragma once
#include <SDL_mixer.h>
#include <iostream>
#include <vector>

class SFX
{
private:
	Mix_Chunk* sound = nullptr;
public:
	SFX();
	~SFX();
	void init();
	void play();
	void stop();
	bool add(std::string path);
};

