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
	SDL_Renderer* renderer = nullptr;
	Uint32 code;
	SDL_Texture* texture = nullptr;
	std::string type;
public:
	Entity(SDL_Renderer* renderer);
	~Entity();
	virtual void init();
	virtual void render();
	SDL_Point getPosition();
	//SDL_Renderer* renderer = nullptr;
	SDL_Rect srcRect;
	SDL_Rect desRect;
	//SDL_Texture* texture = nullptr;
	int map_x, map_y;
	virtual void setProtocolCode();
	void setProtocol();
	SDL_Point position;
	SDL_Rect getRect();
	int getLayer();
	Uint32 getProtocolCode();
};
