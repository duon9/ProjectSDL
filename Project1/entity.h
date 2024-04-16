#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "utils.h"
#include <iostream>
#include "constant.h"
#include "protocol.h"
#include "math.h"

class Entity
{
private:
	static SDL_Texture* vessel;
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
	virtual void setLocation();
	virtual void handleLogic();
	void setLocation(SDL_Point location);
	void setSize(int w, int h);
	static void setTexture(std::string path, SDL_Renderer*renderer);
	SDL_Point getPosition();
	SDL_Rect srcRect;
	SDL_Rect desRect;
	int map_x, map_y;
	virtual void setProtocolCode();
	void setProtocol();
	SDL_Point position;
	SDL_Point getEntityCenterPoint();
	bool check_death = false;
	SDL_Rect getRect();
	int getLayer();
	Uint32 getProtocolCode();
	virtual void handleMissle(int damage);
	virtual void setTexture();
};
