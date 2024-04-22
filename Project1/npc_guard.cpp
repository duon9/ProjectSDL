#include "npc_guard.h"

void Guard::update() {
	lumi->x = desRect.x + desRect.w / 2 - lumi->w / 2;
	lumi->y = desRect.y + desRect.h / 2 - lumi->h / 2;
	//std::cout << "update" << std::endl;
	std::cout << lumi->x << " " << lumi->y << std::endl;
	std::cout << desRect.x << " " << desRect.y << std::endl;
}