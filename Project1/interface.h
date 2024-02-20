#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "entity.h"
#include "utils.h"
#include "constant.h"

class Interface {
private:

	SDL_Renderer* renderer;
	MapName mapName = MapName::WATER_TOWN;
	std::vector<TileLayer> map;
	std::vector<TileSet> tileset;
	SDL_Texture* texture;
	SDL_Rect desRect = { 0, 0 , 32, 32 };
	SDL_Rect srcRect = { 0, 0, 32, 32 };
	int map_w, map_h;


public:
	SDL_Rect camera = { 0, 0, 800, 608 };
	SDL_Rect screen = { 0, 0, 800, 608 };
	Interface(SDL_Renderer* renderer);
	~Interface();

	void init();
	void render();
	void loadTexture();
	void loadMap();

	void cameraInitObjectLocation(int map_x, int map_y, SDL_Rect& object);
	void cameraInitLocation(int map_x, int map_y);
	bool isCameraCollideCornerHorizontal(int velocity);

	bool isCameraCollideCornerVertical(int velocity);
	bool isCenterVertical(SDL_Rect& object);
	bool isCenterHorizontal(SDL_Rect& object);
};