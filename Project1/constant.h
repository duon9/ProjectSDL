#pragma once

enum GameState {
	MENU,
	PLAY,
	EXIT,
	PAUSE
};

enum Orient {
	NORTH,
	WEST,
	EAST,
	SOUTH,
	//NORTHWEST,
	//NORTHEAST,
	//SOUTHEAST,
	//SOUTHWEST,
	NONE
};

enum Option {
	START,
	LOAD,
	QUIT,
	SETTING
};

enum State {
	HEALTHY,
	POISONED,
	BLEEDING,
	BLIND,
	SILENT,
	PARALYZE,
	EXHAUSTED,
};

enum MapTile {
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
	RUNNING,
	TALKING,
	RESTING,
	STANDING,
};

struct blockPosition {
	short row, col;
	blockPosition(short _row = 0, short _col = 0) {
		row = _row;
		col = _col;
	}
};

const short PLAYER_SPEED = 0;
const short PLAYER_HEALTH = 0;
const short PLAYER_LEVEL = 0;
const short PLAYER_MAGIC_DAMAGE = 0;
const short PLAYER_AMMOR = 0;
const short PLAYER_RANGE = 0;
const short PLAYER_MAGIC_RESISTANCE = 0;
const short PLAYER_CRIT = 0;
const short PLAYER_HEAL_RATE = 0;
const short PLAYER_AMMOR_PENETRATION = 0;

const std::string TEST = "assets/.tile/testtile.png";
const std::string TEST1 = "assets/.tile/walls.png";
