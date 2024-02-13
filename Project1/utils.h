#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>
#include <pugixml.hpp>
#include "constant.h"
#include <chrono>

class TextureManagement
{
private:

public:
	TextureManagement();
	~TextureManagement();
	static SDL_Texture* LoadTexture(const std::string filename, SDL_Renderer* renderer);
	static void Draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);
};

class File {
private:
	static void readJSON(std::string path, nlohmann::json& jsondata);

public:
	File();
	~File();

	static std::vector<TileLayer> loadMap(std::string path);
	static std::vector<TileSet> loadTile(std::string path);
	static void readXML(std::string path, std::string& source, int& col);
	static std::vector<std::vector<int>> readCollision(std::string path);
	static void loadObject(SDL_Texture* texture, std::string path);
};
// vector