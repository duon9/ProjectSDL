#include "game.h"
#include "utils.h"
#include <vector>
#include <SDL.h>
#include "constant.h"


int main(int argc, char* argv[])
{
	Game test;
	test.run();
	return 0;

	/*int health, mana, damage, level, exp, speed, map_x, map_y;
	std::string source = "";
	File::getProperties("rogue_knight", health, mana, speed, level, exp, damage, source, map_x, map_y);
	std::cout << health << " " << mana << " " << damage << " " << level << " " << exp << " " << speed << " " << map_x << " " << map_y << std::endl;
	std::cout << source;*/

	/*std::vector<std::vector<SDL_Rect>> res = File::getClips("rogue_knight");
	std::cout << res.size() << " " << res[0].size() << std::endl;
	for (int i = 0; i < res.size(); i++) {
		for (int j = 0; j < res[0].size(); j++) {
			auto at = res[i][j];
			std::cout << at.x << " " << at.y << " " << at.w << " " << at.h << std::endl;
		}

		std::cout << "----------------------------------------------------" << std::endl;
	}*/

	/*std::cout << static_cast<int>(charState::IDLE);*/

	
	return 0;
}