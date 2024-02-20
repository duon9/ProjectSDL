#include "interface.h"

Interface::Interface(SDL_Renderer* renderer) : renderer(renderer) {
	std::cout << ("Interface constructor initialized") << std::endl;

	// Constructor
}

Interface::~Interface() {
	// Deconstructor
}

void Interface::init() {
	/*map = File::loadMap(water_town);
	tileset = File::loadTile(water_town);
	loadTexture();
	loadMap();

	std::cout << map[0].width << " " << map[0].height << std::endl;*/

	/*for (const auto& row : map[0].map) {
		for (const auto& col : row) {
			std::cout << col << " ";
		}
		std::cout << std::endl;
	}*/

	//texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, map[0].width, map[0].height);
	texture = TextureManagement::LoadTexture(TEST, renderer);
	SDL_QueryTexture(texture, NULL, NULL, &map_w, &map_h);
	std::cout << map_w << " " << map_h << std::endl;
}

void Interface::loadMap() {

	auto cached = SDL_GetRenderTarget(renderer);

	SDL_SetRenderTarget(renderer, texture);

	for (auto layer = map.begin(); layer != map.end(); layer++) {
		//std::cout << "load layer" << std::endl;
		int w = layer->width;
		int h = layer->height;

		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				desRect.x = j * desRect.w;
				desRect.y = i * desRect.h;
				//std::cout << "loading block " << i << " " << j << std::endl;
				if (layer->map[i][j] == 0) {
					continue;
				}
				else {
					for (auto tile = tileset.rbegin(); tile != tileset.rend(); tile++) {
						if (layer->map[i][j] >= tile->firstgid) {
							int gid = (layer->map[i][j]) - (tile->firstgid);
							srcRect.x = static_cast<int>(gid % tile->col) * srcRect.w;
							srcRect.y = static_cast<int>(gid / tile->col) * srcRect.h;
							TextureManagement::Draw(renderer, tile->texture, srcRect, desRect);
							break;
						}
					}
				}
			}
		}
	}
	SDL_SetRenderTarget(renderer, cached);
	//TextureManagement::Draw(renderer, texture, srcRect, desRect);
}

void Interface::loadTexture() {
	for (auto it = tileset.begin(); it != tileset.end(); it++) {
		std::cout << File::augmentPath(it->source) << std::endl;
		File::readXML(File::augmentPath(it->source), it->source, it->col);
		//std::cout << it->source << std::endl;
		//std::cout << it->col << std::endl;
		//std::cout << it->firstgid << std::endl;
		std::cout << File::augmentPath(it->source) << std::endl;
		it->texture = TextureManagement::LoadTexture(File::augmentPath(it->source), renderer);
		if (it->texture == nullptr) {
			std::cout << "null interface texture" << std::endl;
		}
	}
	return;
}

void Interface::render() {
	TextureManagement::Draw(renderer, texture, camera, screen);
}

//assets/.tile/tileset/tilesetformattedupdate1.png
//
//assets\.tile\tileset\classical_temple_tiles.png


void Interface::cameraInitObjectLocation(int map_x, int map_y, SDL_Rect& object) {

	cameraInitLocation(map_x, map_y);

	if (map_x * TILE_WIDTH < (screen.w / 2)) {
		object.x = map_x * TILE_WIDTH;
	}
	else if (map_x * TILE_WIDTH + (screen.w / 2) > map_w) {
		object.x = map_x * TILE_WIDTH - camera.x;
	}
	if (map_y * TILE_HEIGHT < (screen.h / 2)) {
		object.y = map_y * TILE_HEIGHT;
	}
	else if (map_y * TILE_HEIGHT + (screen.h / 2) > map_h) {
		object.y = map_y * TILE_HEIGHT - camera.y;
	}
	else {
		object.x = screen.w / 2;
		object.y = screen.h / 2;
	}
}

void Interface::cameraInitLocation(int map_x, int map_y) {
	if (map_x * TILE_WIDTH < (screen.w / 2)) {
		camera.x = 0;
	}
	else if (map_x * TILE_WIDTH + (screen.w / 2) > map_w) {
		camera.x = map_w - screen.w;
	}
	if (map_y * TILE_HEIGHT < (screen.h / 2)) {
		camera.y = 0;
	}
	else if (map_y * TILE_HEIGHT + (screen.h / 2) > map_h) {
		camera.y = map_h - screen.h;
	}
}

bool Interface::isCameraCollideCornerHorizontal(int velocity) {
	if (camera.x + velocity < 0) {
		return true;
	}
	else if (camera.x + camera.w + velocity > map_w) {
		return true;
	}
	return false;
}

bool Interface::isCameraCollideCornerVertical(int velocity) {
	if (camera.y + velocity < 0) {
		return true;
	}
	else if (camera.y + camera.h + velocity > map_h) {
		return true;
	}
	return false;
}

bool Interface::isCenterHorizontal(SDL_Rect& object) {
	if (object.x <= screen.w / 2 + 3 && object.x >= screen.w / 2 - 3) {
		return true;
	}
	return false;
}

bool Interface::isCenterVertical(SDL_Rect& object) {
	if (object.y <= screen.h / 2 + 3 && object.y >= screen.h / 2 - 3) {
		return true;
	}
	return false;
}