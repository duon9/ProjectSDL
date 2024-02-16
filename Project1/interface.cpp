#include "interface.h"

Interface::Interface(SDL_Renderer* renderer) : renderer(renderer) {
	std::cout << ("Interface constructor initialized") << std::endl;

	// Constructor
}

Interface::~Interface() {
	// Deconstructor
}

void Interface::init() {
	//map = File::loadMap(water_town);
	//tileset = File::loadTile(water_town);
	//load();
	texture = TextureManagement::LoadTexture(TEST, renderer);
}

void Interface::render() {
	//for (auto layer = map.begin(); layer != map.end(); layer++) {
	//	//std::cout << "load layer" << std::endl;
	//	int w = layer->width;
	//	int h = layer->height;

	//	for (int i = 0; i < h; i++) {
	//		for (int j = 0; j < w; j++) {
	//			desRect.x = j * desRect.w;
	//			desRect.y = i * desRect.h;
	//			//std::cout << "loading block " << i << " " << j << std::endl;
	//			if (layer->map[i][j] == 0) {
	//				continue;
	//			}
	//			else {
	//				for (auto tile = tileset.rbegin(); tile != tileset.rend(); tile++) {
	//					if (layer->map[i][j] >= tile->firstgid) {
	//						int gid = (layer->map[i][j]) - (tile->firstgid);
	//						srcRect.x = static_cast<int>(gid % tile->col) * srcRect.w;
	//						srcRect.y = static_cast<int>(gid / tile->col) * srcRect.h;
	//						TextureManagement::Draw(renderer, tile->texture, srcRect, desRect);
	//						break;
	//					}
	//				}
	//			}
	//		}
	//	}
	//}

	TextureManagement::Draw(renderer, texture, srcRect, desRect);
}

void Interface::load() {
	//for (auto it = tileset.begin(); it != tileset.end(); it++) {
	//	File::readXML(it->source, it->source, it->col);
	//	std::cout << it->source << std::endl;
	//	std::cout << it->col << std::endl;
	//	std::cout << it->firstgid << std::endl;

	//	it->texture = TextureManagement::LoadTexture(it->source, renderer);
	//	if (it->texture == nullptr) {
	//		std::cout << "null interface texture" << std::endl;
	//	}
	//}
	//return;
}