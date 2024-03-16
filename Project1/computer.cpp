#include "computer.h"

void Computer::chaseTarget(Player* target) {
	if (!check_death && !check_pause) {
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
	//std::cout << stat.health << std::endl;
	/*for (auto target = targets.begin(); target != targets.end(); target++) {
		if ((*target)->isInvisible || (*target)->check_death) continue;
		Math::Vector v = Math::Vector(position, (*target)->getPosition());
		if (v.Math::Vector::getDistance() < (10 * TILE_WIDTH)) {
			return *target;
		}
	}*/

	if (target->isInvisible || target->check_death) return false;
	Math::Vector v = Math::Vector(position, target->getPosition());
	if (v.Math::Vector::getDistance() < (10 * TILE_WIDTH)) return true;
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
			position.x += v.getX() * stat.speed;
		}
		//position.x += v.getX() * stat.speed;

		if (!collision->isCollidingVertical(v.getY() * stat.speed)) {
			position.y += v.getY() * stat.speed;
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
	if (v.getDistance() <= (int)(5*TILE_WIDTH)) {
		return true;
	}
	return false;
}


void Computer::setProtocolCode() {
	code = ENEMY_CODE;
}


