#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "utils.h"
#include <iostream>
#include "constant.h"

class Entity
{
public:
	Entity(SDL_Renderer* renderer);
	~Entity();
	virtual void init();
	virtual void render();
	virtual void free();
	SDL_Renderer* renderer = nullptr;
	short width, height;
	std::string name;
};
