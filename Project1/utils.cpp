#include "utils.h"
#include <random>
#include <ctime>

TextureManagement::TextureManagement() {
}

TextureManagement::~TextureManagement() {
}

SDL_Texture* TextureManagement::LoadTexture(const std::string filename, SDL_Renderer* renderer) {
	SDL_Surface* tempSurface = IMG_Load(filename.c_str());
	SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	//SDL_SetTextureBlendMode(tempTexture, SDL_BLENDMODE_NONE);
	SDL_FreeSurface(tempSurface);
	return tempTexture;
}

void TextureManagement::Draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect src, SDL_Rect dest) {
	SDL_RenderCopy(renderer, texture, &src, &dest);
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

void File::getProperties(std::string type, int& health, int& mana, int& speed, int& level, int& exp, int& damage, std::string& source, int& map_x, int& map_y) {
	nlohmann::json jsondata;
	readJSON(file_object, jsondata);
	nlohmann::json object = jsondata[type];
	health = object["health"].get<int>();
	mana = object["mana"].get<int>();
	damage = object["damage"].get<int>();
	level = object["level"].get<int>();
	exp = object["exp"].get<int>();
	speed = object["speed"].get<int>();
	source = object["source"].get<std::string>();
	map_x = object["map_x"].get<int>();
	map_y = object["map_y"].get<int>();
}


//enum charState {
//	IDLE,
//	RUNNING,
//	ATTACKING,
//	DEATH,
//	SPELLCAST,
//	TAKEDAMAGE
//	
//};


std::vector<std::vector<SDL_Rect>> File::getClips(std::string type) {
	std::vector<std::vector<SDL_Rect>> res;
	SDL_Rect temp;
	nlohmann::json jsondata;
	readJSON(file_object, jsondata);
	nlohmann::json entity = jsondata["rogue_knight"];
	std::cout << "load object finish \n";
	nlohmann::json clips = entity["clips"];

	std::cout << "load clips finish \n";

	for (const auto& clip : clips) {
		std::vector<SDL_Rect> frame;
		int count = clip["count"];

		if (count == 0) {
			continue;
		}
		else {
			nlohmann::json ware = clip["srcRect"];
			nlohmann::json present = clip["desRect"];
			if (ware.is_array()) {
				for (const auto& action : ware) {
					//temp = { ware[i][0], ware[i][1], ware[i][2], ware[i][3] };
					temp = { action[0], action[1], action[2], action[3] };
					frame.push_back(temp);
				}
			}
		}

		res.push_back(frame);
	}
	return res;
}