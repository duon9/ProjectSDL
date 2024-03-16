#pragma once
#include "computer.h"
class Minotaur : public Computer
{
private:
	static SDL_Texture* vessel;
	static Stat base;
public:
	static void setTexture(std::string path, SDL_Renderer* renderer);
	static void setBase();
};

