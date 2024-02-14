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
	static void getProperties(std::string type, int& health, int& mana, int& speed, int& level, int& exp, int& damage, std::string& source, int& map_x, int& map_y);
	static std::vector<std::vector<SDL_Rect>> getClips(std::string type);
};
// vector

//namespace luckywheel {
//	int ranint(int first, int last) {
//		std::mt19937 rng(std::time(nullptr)); // get current time
//		std::uniform_int_distribution<int> distribution(first, last); // get random orient
//		return distribution(rng);
//	}
//}

//void getProperties(std::string type, int& health, int& mana, int& speed, int& level, int& exp, int& damage, std::string& source, int& map_x, int& map_y) {
//	nlohmann::json jsondata;
//	readJSON(path, jsondata);
//	nlohmann::json object = jsondata[type];
//	health = object["health"].get<int>();
//	mana = object["mana"].get<int>();
//	damage = object["damage"].get<int>();
//	level = object["level"].get<int>();
//	exp = object["exp"].get<int>();
//	speed = object["speed"].get<int>();
//	source = object["source"].get<std::string>();
//	map_x = object["map_x"].get<int>();
//	map_y = object["map_y"].get<int>();
//}