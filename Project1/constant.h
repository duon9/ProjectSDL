#pragma once
#include <SDL.h>

enum GameState {
	MENU,
	PLAY,
	EXIT,
	PAUSE
};

enum Option {
	START,
	LOAD,
	QUIT,
	SETTING
};

struct Orient {
	int up = 0;
	int down = 0;
	int left = 0;
	int right = 0;

	Orient(int _up = 0, int _down = 0, int _left = 0, int _right = 0) {
		up = _up;
		down = _down;
		left = _left;
		right = _right;
	}
};

enum MapName {
	VILLAGE,
	FRONTIER_TOWN,
	CAPITAL,
	WATER_TOWN,
	PEARL_HARBOR,
	FROST_HILL,
	ELF_WOOD,
	DWARF_FORTRESS,
};

enum charState {
	ATTACKING,
	RUNNING,
	TALKING,
	CASTING,
	IDLE,
	DEATH
};

struct blockPosition {
	short row, col;
	blockPosition(short _row = 0, short _col = 0) {
		row = _row;
		col = _col;
	}
};

struct TileLayer {
	std::string name;
	int height;
	int width;
	std::vector<std::vector<int>> map;
};

struct TileSet {
	int firstgid;
	std::string source;
	int col;
	SDL_Texture* texture = nullptr;
};

const int PLAYER_SPEED = 7;
const int PLAYER_HEALTH = 1000;
const int PLAYER_MANA = 500;
const int PLAYER_LEVEL = 1;
const int PLAYER_MAGIC_DAMAGE = 15;
const int PLAYER_ARMOR = 1;
const int PLAYER_RANGE = 1;
const int PLAYER_MAGIC_RESISTANCE = 1;

const int SPEED = 5;

const std::string TEST = "assets/.tile/testtile.png";
const std::string TEST1 = "assets/.tile/walls.png";
const std::string water_town = "assets/.tile/test2.tmj";
const std::string ROGUE = "assets/characters/rogue.png";
const std::string littleboy = "assets/characters/player.png";
const std::string VIKING = "assets/characters/viking.png";
const std::string DARK = "assets/characters/dark.png";