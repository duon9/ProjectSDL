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
	Orient getOrient();
	blockPosition getBlockPos();
	void updateOrient(Orient tmpOrient);
	void updateBlockPos(blockPosition tmpBlockPos);
	virtual void init();
	virtual void render();
	virtual void free();

protected:
	SDL_Renderer* renderer = nullptr;
	Orient curr_orient;
	blockPosition currBlockPos;
	short width, height;
	char name[15];
};
