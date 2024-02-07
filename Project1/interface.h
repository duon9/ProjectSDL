#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "utils.h"
#include "constant.h"

class Interface {
private:

	SDL_Renderer* renderer;
	MapName mapName = MapName::WATER_TOWN;
	std::vector<TileLayer> map;
	std::vector<TileSet> tileset;
	SDL_Rect desRect = { 0, 0 , 32, 32 };
	SDL_Rect srcRect = { 0, 0, 32, 32 };

public:

	Interface(SDL_Renderer* renderer);
	~Interface();

	void init();
	void render();
	void load();
};