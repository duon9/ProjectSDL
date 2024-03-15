#include "interface.h"
#include "collision.h"

Interface::Interface(SDL_Renderer* renderer, Map* map) {
	std::cout << ("Interface constructor initialized") << std::endl;
	this->renderer = renderer;
	this->Imap = map;
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
	health_display = new Bar(renderer, 25, SCREEN_HEIGHT - 30, 100, 15, {255,0,0,255});
	mana_display = new Bar(renderer, 25, SCREEN_HEIGHT -50, 100, 15, {3,161,252,255});
	//parameter = new FPSparameter(renderer, 25, 25, 50, 25);
	//parameter->init();
	//texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, map[0].width, map[0].height);
	//texture = TextureManagement::LoadTexture("assets/.tile/underground.png", renderer);
	texture = TextureManagement::LoadTexture("assets/map/republic_grey.png", renderer);
	SDL_QueryTexture(texture, NULL, NULL, &map_w, &map_h);
	//std::cout << map_w << " " << map_h << std::endl;
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
	//parameter->render();
	TextureManagement::Draw(renderer, texture, camera, screen);
	health_display->render();
	mana_display->render();
}

void Interface::handleInterfaceEvents() {
	//health_display->updateBar();
	//mana_display->updateBar();
}

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
		object.x = screen.w / 2 - object.w / 2;
		object.y = screen.h / 2 - object.h / 2;
	}
}

void Interface::cameraInitLocation(int map_x, int map_y) {
	if (map_x * TILE_WIDTH < (screen.w / 2)) {
		camera.x = 0;
	}
	else if (map_x * TILE_WIDTH + (screen.w / 2) > map_w) {
		camera.x = map_w - screen.w;
	}
	else {
		camera.x = map_x * TILE_WIDTH - screen.w / 2;
	}
	if (map_y * TILE_HEIGHT < (screen.h / 2)) {
		camera.y = 0;
	}
	else if (map_y * TILE_HEIGHT + (screen.h / 2) > map_h) {
		camera.y = map_h - screen.h;
	}
	else {
		camera.y = map_y * TILE_HEIGHT - screen.h / 2;
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
	if (object.x <= screen.w / 2 + 3 - object.w / 2 && object.x >= screen.w / 2 - 3 - object.w / 2) {
		return true;
	}
	return false;
}

bool Interface::isCenterVertical(SDL_Rect& object) {
	if (object.y <= screen.h / 2 - object.h / 2 + 3 && object.y >= screen.h / 2 - 3 - object.h / 2) {
		return true;
	}
	return false;
}

void Interface::updateObjectScreenPosition(SDL_Point& position, SDL_Rect& object) {
	object.x = position.x - camera.x;
	object.y = position.y - camera.y;
}
