#include "FireWorm.h"

SDL_Texture* FireWorm::vessel = nullptr;

void FireWorm::draw() {
	SDL_RenderCopyEx(renderer, FireWorm::vessel, &srcRect, &desRect, NULL, NULL, flip);
}

void FireWorm::chaseTarget(Player* target) {
	if (!check_death && !check_pause) {
		if (trackNearestTarget(target)) {
			if (!moveTo(target->getPosition())) {
				if (frameTick > 0) {
					if (frameTick == 50) {
						FireBomb* bomb = new FireBomb(renderer, getPosition(), target->getPosition(), {0,0}, code);
						global::missles.push_back(bomb);
					}
					frameTick--;
					return;
				}
				status = ATTACKING;
				frameTick = frame[status].maxFrame;
			}
		}
		else {
			//std::cout << "not found player" << std::endl;
			status = IDLE;
		}
	}
}