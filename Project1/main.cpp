#include "game.h"
#include "utils.h"

int main(int argc, char* argv[])
{
	/*Game test;
	test.run();
	return 0;*/

	int health, mana, damage, level, exp, speed, map_x, map_y;
	std::string source = "";
	File::getProperties("rogue_knight", health, mana, speed, level, exp, damage, source, map_x, map_y);
	std::cout << health << " " << mana << " " << damage << " " << level << " " << exp << " " << speed << " " << map_x << " " << map_y << std::endl;
	std::cout << source;
	return 0;
}