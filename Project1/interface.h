#pragma once
#include "entity.h"
#include "utils.h"
#include "constant.h"
#include "statsBar.h"
#include "dialogue_box.h"
#include "pauseWindow.h"
//#include "computer.h"

class Interface {
private:
	//healthBar* health_display = nullptr;
	//SDL_Rect lightRect = { 0,0,360,360 };
	SDL_Renderer* renderer;
	Map* Imap = nullptr;
	std::vector<TileLayer> map;
	std::vector<TileSet> tileset;
	SDL_Texture* texture;
	SDL_Rect desRect = { 0, 0 , 32, 32 };
	SDL_Rect srcRect = { 0, 0, 32, 32 };
	int map_w, map_h;
	DialogueBox& box = DialogueBox::getInstance();
	PauseWindow& pw = PauseWindow::getInstance();
	SDL_Texture* dark = nullptr;
	SDL_Texture* light = nullptr;
public:
	Bar* health_display = nullptr;
	Bar* mana_display = nullptr;
	SDL_Rect camera = { 0, 0, 800, 608 };
	SDL_Rect screen = { 0, 0, 800, 608 };
	Interface(SDL_Renderer* renderer, Map * map);
	~Interface();

	void init();
	void render();
	void renderUpward();
	void handleInterfaceEvents();
	void loadTexture();
	void loadMap();

	void cameraInitObjectLocation(int map_x, int map_y, SDL_Rect& object);
	void cameraInitLocation(int map_x, int map_y);
	bool isCameraCollideCornerHorizontal(int velocity);

	bool isCameraCollideCornerVertical(int velocity);
	bool isCenterVertical(SDL_Rect& object);
	bool isCenterHorizontal(SDL_Rect& object);
	void updateObjectScreenPosition(SDL_Point& position, SDL_Rect& object);
	void reload(std::string path);
	void light2D();
};