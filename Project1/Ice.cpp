#include "Ice.h"
#include "collision.h"
void Ice::create() {
	//std::cout << "XXXXXXXXXXXXXXXXXXXXX" << std::endl;
	//std::cout << (position.x + desRect.w / 2) << " " << (position.y + desRect.h) << std::endl;
	Collision::update({ (position.y + desRect.h) / 32,(position.x + desRect.w / 2) / 32 }, 0);
}

void Ice::handleLogic() {
	if (!check_death) {
		if (stat.health <= 0) {
			clear();
			status = ENDING;
			frameCount = 0;
			check_death = true;
		}
	}
}

void Ice::clear() {
	Collision::update({ (position.y + desRect.h) / 32,(position.x + desRect.w / 2) / 32 }, 1);
}