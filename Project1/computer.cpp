#include "computer.h"

void Computer::chaseTarget(Player* target) {

	if (check_death) {
		death();
		return;
	}

	if (!check_death && !global::isPause) {
		if (trackNearestTarget(target)) {
			if (!moveTo(target->getPosition())) {
				if (frameTick > 0) {
					//status = IDLE;
					frameTick--;
					return;
				}
				status = ATTACKING;
				attack();
			}
		}
		else {
			//std::cout << "not found player" << std::endl;
			status = IDLE;
		}
	}
}

bool Computer::trackNearestTarget(Player* target) {
	if (target->isInvisible || target->check_death) return false;
	Math::Vector v = Math::Vector(position, target->getPosition());
	if (v.Math::Vector::getDistance() < (range * TILE_WIDTH)) return true;
	return false;
}

bool Computer::moveTo(SDL_Point target) {
	Math::Vector v = Math::Vector(position, target);

	if (v.getX() < 0) flip = SDL_FLIP_HORIZONTAL;
	if (v.getX() > 0) flip = SDL_FLIP_NONE;
	if (!isReachDestination(v)) {
		status = RUNNING;
		v = v / v.getDistance();

		if (!collision->isCollidingHorizontal(v.getX() * stat.speed)) {
			//std::cout << position.x + stat.speed * v.getX() << std::endl;
			position.x = position.x + (v.getX() * stat.speed); // speed should > 1 to prevent error
			//std::cout << "X: " << position.x << std::endl;
		}
		else {
			//std::cout << "BlockX" << std::endl;
		}
		//position.x += v.getX() * stat.speed;

		if (!collision->isCollidingVertical(v.getY() * stat.speed)) {
			//std::cout << stat.speed * v.getY() << std::endl;
			position.y = position.y + (v.getY() * stat.speed); // speed should > 1 to prevent error
		}
		else {
			//std::cout << "BlockY" << std::endl;
		}
		//position.y += v.getY() * stat.speed;
		return true;
	}
	else {
		//std::cout << "reach target" << std::endl;
		return false;
	}
}

bool Computer::isReachDestination(Math::Vector v) {
	if (v.getDistance() <= (int)(stat.range*TILE_WIDTH)) {
		return true;
	}
	return false;
}


void Computer::setProtocolCode() {
	code = ENEMY_CODE;
}

bool Computer::moveToBlock(SDL_Point block) {
	if (moveTo({ block.x * 32 + 16, block.y * 32 + 16 }) == true) {
		return true;
	}
	return false;
}

SDL_Point Computer::shortestSmartPath() {
	return { 0,0 };
}

void Computer::gift() {
	manager.check(type);
}