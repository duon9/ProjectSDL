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
	 IDLE,
	 RUNNING,
	 ATTACKING,
	 DEATH,
	 SPELLCAST,
	 TAKEDAMAGE
	/*ATTACKING,
	RUNNING,
	TALKING,
	CASTING,
	IDLE,
	DEATH*/
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

struct Stat {
	int health;
	int mana;
	int damage;
	int level;
	int exp;
	int speed;
	std::string source;
	int range;
	int speed_ratio;

	Stat(int _health, int _mana, int _damage, int _level, int _exp, int _speed, std::string _source, int _range) {
		health = _health;
		mana = _mana;
		damage = _damage;
		level = _level;
		exp = _level;
		speed = _speed;
		source = _source;
		range = _range;
		speed_ratio = 1;
	}

	Stat() {
		std::cout << "Stat called \n";
	}
};

struct Frame {
	int maxFrame;
	int perFrame;
	int count;
};

const int RUN_FRAMETICK = 40;
const int ATTACK_FRAMETICK = 100;
const int MAX_IDLE_FRAMECOUNT = 200 - 1;
const int MAX_RUN_FRAMECOUNT = 40 - 1;
const int MAX_ATTACK_FRAMECOUNT = 100 - 1;
const int MAX_DEAD_FRAMECOUNT = 100 - 1;
const int MAX_STATUS = 6;
const int OBJECT_WIDTH = 64;
const int OBJECT_HEIGHT = 64;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 608;
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;

const int MAX_VIEW_BLOCK_HORIZONTAL = 12;
const int MAX_VIEW_BLOCK_VERTICAL = 9;

const int PLAYER_SPEED = 4;
const int PLAYER_HEALTH = 1000;
const int PLAYER_MANA = 500;
const int PLAYER_LEVEL = 1;
const int PLAYER_MAGIC_DAMAGE = 15;
const int PLAYER_ARMOR = 1;
const int PLAYER_RANGE = 1;
const int PLAYER_MAGIC_RESISTANCE = 1;

const int SPEED = 5;

const std::string TEST = "assets/.tile/map.png";
const std::string TEST1 = "assets/.tile/walls.png";
const std::string water_town = "assets/.tile/underground.tmj";
const std::string ROGUE = "rogue_knight";
const std::string littleboy = "assets/characters/player.png";
const std::string VIKING = "assets/characters/viking.png";
const std::string DARK = "assets/characters/dark.png";
const std::string file_object = "assets/characters/object.json";