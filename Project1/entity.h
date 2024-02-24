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
	//short width, height;
	std::string name;
	SDL_Rect srcRect;
	SDL_Rect desRect;
	SDL_Texture* texture = nullptr;
	int map_x, map_y;
	int x, y; // the bottom center of object's rect
};
