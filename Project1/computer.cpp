#include "computer.h"
#include "math.h"

void Computer::randomBotMovement() {
	if (!check_death && !check_pause) {
		if (find_enemy) {
			return;
		}
		else {

		}
	} 
}

void Computer::chaseTarget(std::vector<Player*>* targets) {
	Player* victim = trackNearestTarget(targets);
	if (victim != nullptr) {
		//std::cout << "found player, start hunting" << std::endl;
		moveTo(victim->getPosition());
	}
	else {
		//std::cout << "not found player" << std::endl;
		status = IDLE;
	}
}

Player* Computer::trackNearestTarget(std::vector<Player*>* targets) {
	//std::cout << stat.health << std::endl;
	for (auto target = targets->begin(); target != targets->end(); target++) {
		if ((*target)->isInvisible) continue;
		Math::Vector v = Math::Vector(position, (*target)->getPosition());
		if (v.Math::Vector::getDistance() < (10 * TILE_WIDTH)) {
			return *target;
		}
	}
	return nullptr;
}

void Computer::moveTo(SDL_Point target) {
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
	}
	else {
		//std::cout << "reach target" << std::endl;
		status = IDLE;
	}
}

bool Computer::isReachDestination(Math::Vector v) {
	if (v.getDistance() <= 1*TILE_WIDTH) {
		return true;
	}
	return false;
}

void Computer::setProtocolCode() {
	code = ENEMY_CODE;
}