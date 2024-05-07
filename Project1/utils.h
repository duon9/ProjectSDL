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
#include <unordered_map>
#include "QuestManager.h"

class TextureManagement
{
private:

public:
	TextureManagement();
	~TextureManagement();
	static SDL_Texture* LoadTexture(const std::string filename, SDL_Renderer* renderer);
	static SDL_Texture* LoadText(SDL_Renderer* renderer, TTF_Font* font, std::string text, SDL_Color color = {0,0,0,255});
	static void loadTextRect(SDL_Texture* texture, SDL_Rect& textRect, SDL_Rect button);
	static void Draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);
	static void Draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
	static void DrawRect(SDL_Renderer* renderer, SDL_Color color, SDL_Rect object);
	static SDL_Texture* LoadTargetTexture(const std::string filepath, SDL_Renderer* renderer);
	static void FillRect(SDL_Renderer* renderer, SDL_Color color, SDL_Rect object);
};

class File {
private:
	
	
public:
	File();
	~File();
	static std::string augmentPath(std::string path);
	static void readJSON(std::string path, nlohmann::json& jsondata);
	static std::vector<TileLayer> loadMap(std::string path);
	static std::vector<TileSet> loadTile(std::string path);
	static void readXML(std::string path, std::string& source, int& col);
	static std::vector<std::vector<int>> readCollision(std::string path);
	static void getProperties(std::string type, Stat* stat);
	static std::vector<std::vector<SDL_Rect>> getClips(std::string type);
	static void getFrameLimit(std::string type, std::vector<Frame>* frame);

	static void writeSaveGame(
		int health, // current health of player
		int mana, // current mana of player
		int exp, // current exp of player
		SDL_Point location, // current location of player
		int quest_curr, // current quest index
		int quest_progress,
		Map curr_map // current map
	);

	static void readSaveGame(
		Stat& stat, 
		SDL_Point& location,
		Map& map,
		QuestManager& quest
	);

};

namespace Global {
	extern GameState gamestate;
	extern Map map;
	//extern std::unordered_map<std::string, SDL_Texture*> preload;
	//extern SDL_Renderer* renderer;
}

namespace Font {
	TTF_Font* loadFont(std::string font, int size);
	//void loadTextRect(SDL_Texture* texture, SDL_Rect& textRect, SDL_Rect button);
}
