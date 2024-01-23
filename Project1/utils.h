#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <fstream>
#include <vector>

class TextureManagement
{
private:

public:
	TextureManagement();
	~TextureManagement();
	static SDL_Texture* LoadTexture(const std::string filename, SDL_Renderer* renderer);
	static void Draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);
};


class Map {
private:

public:
	Map();
	~Map();
	static std::vector<std::vector<int>> loadMap(std::string path);
};