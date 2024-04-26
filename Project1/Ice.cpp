#include "Ice.h"
#include "collision.h"
void Ice::create() {
	//std::cout << "XXXXXXXXXXXXXXXXXXXXX" << std::endl;
	std::cout << (position.x + desRect.w / 2) << " " << (position.y + desRect.h) << std::endl;
	Collision::update({ (position.y + desRect.h) / 32,(position.x + desRect.w / 2) / 32 });
}