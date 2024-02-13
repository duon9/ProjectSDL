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
#include <random>
#include <ctime>

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

//namespace luckywheel {
//	int ranint(int first, int last) {
//		std::mt19937 rng(std::time(nullptr)); // get current time
//		std::uniform_int_distribution<int> distribution(first, last); // get random orient
//		return distribution(rng);
//	}
//}