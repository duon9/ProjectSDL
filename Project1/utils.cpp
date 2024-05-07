#include "utils.h"
#include <random>
#include <ctime>

SDL_Texture* TextureManagement::LoadTexture(const std::string filename, SDL_Renderer* renderer) {
	SDL_Surface* tempSurface = IMG_Load(filename.c_str());
	SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	//SDL_SetTextureBlendMode(tempTexture, SDL_BLENDMODE_NONE);
	SDL_FreeSurface(tempSurface);
	return tempTexture;
}

SDL_Texture* TextureManagement::LoadText(SDL_Renderer* renderer, TTF_Font* font, std::string text, SDL_Color color) {
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}

void TextureManagement::loadTextRect(SDL_Texture* texture, SDL_Rect& textRect, SDL_Rect button) {
	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	textRect.x = button.x + button.w / 2 - w / 2;
	textRect.y = button.y + button.h / 2 - h / 2;
	textRect.w = w;
	textRect.h = h;
}

SDL_Texture* TextureManagement::LoadTargetTexture(std::string filepath, SDL_Renderer* renderer) {
	SDL_Surface* tempSurface = IMG_Load(filepath.c_str());
	SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	//SDL_SetTextureBlendMode(tempTexture, SDL_BLENDMODE_NONE);
	SDL_FreeSurface(tempSurface);
	return tempTexture;
}

std::string File::augmentPath(std::string path) {

	if (path[0] == '.' && path[1] == '.') {
		path = path.substr(3);
	}

	return "assets\/.tile\/" + path;
}

void TextureManagement::Draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect src, SDL_Rect dest) {
	SDL_RenderCopy(renderer, texture, &src, &dest);
}

void TextureManagement::FillRect(SDL_Renderer* renderer, SDL_Color color, SDL_Rect object) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &object);
}

void TextureManagement::Draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip) {
	SDL_RenderCopyEx(renderer, texture, &src, &dest, NULL, NULL, flip);
}

void TextureManagement::DrawRect(SDL_Renderer* renderer, SDL_Color color, SDL_Rect object) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(renderer, &object);
}

void File::readJSON(std::string path, nlohmann::json& jsondata) {
	std::ifstream file(path);
	if (!file.is_open()) {
		std::cout << "Cannot open file \n";
	}
	else {
		file >> jsondata;
		file.close();
	}
}

std::vector<TileLayer> File::loadMap(std::string path) {
	nlohmann::json jsondata;
	readJSON(path, jsondata);

	nlohmann::json layers = jsondata["layers"];
	std::vector<TileLayer> tilelayer;

	for (const auto& layer : layers) {
		if (layer["name"] == "collision") {
			continue;
		}
		else {
			nlohmann::json data = layer["data"];
			TileLayer tile;
			int h = layer["height"];
			int w = layer["width"];

			tile.height = h;
			tile.width = w;

			for (int i = 0; i < h; i++) {
				std::vector<int> v;
				for (int j = w * i; j < (i + 1) * w; j++) {
					int value = data[j];
					v.push_back(value);
				}
				tile.map.push_back(v);
			}
			tilelayer.push_back(tile);
		}
	}
	return tilelayer;
}

std::vector<TileSet> File::loadTile(std::string path) {
	nlohmann::json jsondata;
	readJSON(path, jsondata);

	std::vector<TileSet> v;
	nlohmann::json tilesets = jsondata["tilesets"];

	for (const auto& tileset : tilesets) {
		TileSet tile;
		tile.firstgid = tileset["firstgid"];
		tile.source = tileset["source"];
		v.push_back(tile);
	}
	return v;
}

void File::readXML(std::string path, std::string& source, int& col) {
	pugi::xml_document doc;
	doc.load_file(path.c_str());

	pugi::xml_node tileset = doc.child("tileset");
	pugi::xml_node image = tileset.child("image");
	col = tileset.attribute("columns").as_int();
	source = image.attribute("source").as_string();
	return;
}

std::vector<std::vector<int>> File::readCollision(std::string path) {
	std::vector<std::vector<int>> res;
	nlohmann::json jsondata;
	readJSON(path, jsondata);

	nlohmann::json layers = jsondata["layers"];

	for (const auto& layer : layers) {
		if (layer["name"] == "collision") {
			nlohmann::json data = layer["data"];
			int h = layer["height"];
			int w = layer["width"];

			for (int i = 0; i < h; i++) {
				std::vector<int> v;
				for (int j = w * i; j < (i + 1) * w; j++) {
					int value = data[j];
					v.push_back(value);
				}
				res.push_back(v);
			}
		}
	}
	return res;
}

void File::getProperties(std::string type, Stat* stat) {
	nlohmann::json jsondata;
	readJSON(file_object, jsondata);
	//std::string state[] = { "idleFrame", "runFrame", "attackFrame", "deathFrame", "spellFrame", "takedameFrame" };
	nlohmann::json object = jsondata[type];
	stat->health = object["health"].get<int>();
	stat->mana = object["mana"].get<int>();
	stat->damage = object["damage"].get<int>();
	stat->level = object["level"].get<int>();
	stat->exp = object["exp"].get<int>();
	stat->speed = object["speed"].get<int>();
	stat->source = object["source"].get<std::string>();
	stat->range = object["range"].get<int>();
	stat->width = object["width"].get<int>();
	stat->height = object["height"].get<int>();
}


std::vector<std::vector<SDL_Rect>> File::getClips(std::string type) {
	std::vector<std::vector<SDL_Rect>> res;
	SDL_Rect temp;
	nlohmann::json jsondata;
	readJSON(file_object, jsondata);
	nlohmann::json entity = jsondata[type];
	nlohmann::json clips = entity["clips"];
	
	std::string state[] = { "idleFrame", "runFrame", "attackFrame", "deathFrame", "takedameFrame", "spellFrame" };
	for (int i = 0; i < MAX_STATUS; i++) {
		nlohmann::json clip = clips[state[i]];
		std::vector<SDL_Rect> frame;
		int count = clip["count"];
		if (count == 0) {
			continue;
		}
		else {
			std::cout << state[i] << std::endl;
			nlohmann::json ware = clip["srcRect"];
			// desRect here in future
			if (ware.is_array()) {
				for (int i = 0; i < count; i++) {
					temp = { ware[i][0], ware[i][1], ware[i][2], ware[i][3] };
					frame.push_back(temp);
				}
			}
		}
		res.push_back(frame);
	}
	return res;
}

void File::getFrameLimit(std::string type, std::vector<Frame>* frame) {
	nlohmann::json jsondata;
	readJSON(file_object, jsondata);
	std::string state[] = { "idleFrame", "runFrame", "attackFrame", "deathFrame", "takedameFrame", "spellFrame" };
	nlohmann::json clips = jsondata[type]["clips"];
	for (int i = 0; i < MAX_STATUS; i++) {
		Frame temp;
		nlohmann::json clip = clips[state[i]];
		temp.count = clip["count"].get<int>();

		if (temp.count == 0) continue;

		temp.maxFrame = clip["maxFrame"].get<int>();
		temp.perFrame = temp.maxFrame / temp.count;
		frame->push_back(temp);
	}
}

GameState Global::gamestate = MENU;

TTF_Font* Font::loadFont(std::string path, int size) {
	TTF_Font* font = TTF_OpenFont(path.c_str(), size);
	return font;
}

//void Font::loadTextRect(SDL_Texture* texture, SDL_Rect& textRect, SDL_Rect button) {
//	int w, h;
//	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
//	textRect.x = button.x + button.w / 2 - w / 2;
//	textRect.y = button.y + button.h / 2;
//	textRect.w = w;
//	textRect.h = h;
//}

void File::writeSaveGame(
	int health, // current health of player
	int mana, // current mana of player
	int exp, // current exp of player
	SDL_Point location, // current location of player
	int quest_curr, // current quest index
	int quest_progress, // current progress of mission
	Map curr_map // current map, this will transform to int to store in json
) {
	/*
	* This function is used to write saved information when save
	* Current state of player will save under json type, and save at save.json
	* The structure of json file will be:
	* 
	* "player" : {
	*	"health" : health,
	*	"mana" : mana,
	*	"exp" : exp
	*	"XOffset" : location.x,
	*	"YOffset" : location.y
	* },
	* "quest" {
	*	"current" : quest_curr,
	*	"progress" : quest_progress
	* },
	* "map" {
	*	map : (int)curr_map
	* }
	*/

	std::ofstream file("save.json", std::ofstream::out | std::ofstream::trunc);
	if (!file.is_open()) {
		std::cerr << "Cannot open file" << std::endl;
		return;
	}

	nlohmann::json j;

	j["player"] = {
		{"health", health},
		{"mana", mana},
		{"exp", exp},
		{"XOffset", location.x},
		{"YOffset", location.y}
	};

	j["quest"] = {
		{"current", quest_curr},
		{"progress", quest_progress}
	};

	j["map"] = {
		{"map", static_cast<int>(curr_map)}
	};

	file << std::setw(4) << j << std::endl;

	file.close();
}

void File::readSaveGame(
	Stat& stat, // stat of player
	SDL_Point& location, // location of player
	Map& map, // map
	QuestManager& quest // quest
) {
	/*
	* this function is used to load the saved gamestate
	* The saved information will read from save.json
	*/
	nlohmann::json jsondata;
	readJSON("save.json", jsondata);
	nlohmann::json player = jsondata["player"];
	stat.health = player["health"];
	stat.mana = player["mana"];
	stat.exp = player["exp"];
	location.x = player["XOffset"];
	location.y = player["YOffset"];
	nlohmann::json questr = jsondata["quest"];
	quest.setMission(questr["current"]);
	quest.setProgress(questr["progress"]);
	map = static_cast<Map>(jsondata["map"]["map"]);
}