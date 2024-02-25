#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "utils.h"
#include <iostream>
#include "constant.h"
#include "protocol.h"

class Entity
{
protected:
	Protocol* protocol = nullptr;
public:
	Entity(SDL_Renderer* renderer);
	~Entity();
	virtual void init();
	virtual void render();
	virtual void free();
	SDL_Renderer* renderer = nullptr;
	//short width, height;
	Uint32 code;
	SDL_Rect srcRect;
	SDL_Rect desRect;
	SDL_Texture* texture = nullptr;
	int map_x, map_y;
	int x, y; // the bottom center of object's rect
	virtual void setProtocolCode();
	void setProtocol();
};
