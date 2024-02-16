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
	SDL_Texture* texture;
	SDL_Rect desRect = { 0, 0 , 800, 608 };
	//SDL_Rect srcRect = { 0, 0, 800, 608 };

public:
	SDL_Rect srcRect = { 0, 0, 400, 608 / 2 };
	Interface(SDL_Renderer* renderer);
	~Interface();

	void init();
	void render();
	void load();
};