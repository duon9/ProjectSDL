#include "FireWorm.h"

SDL_Texture* FireWorm::vessel = nullptr;

void FireWorm::draw() {
	SDL_RenderCopyEx(renderer, FireWorm::vessel, &srcRect, &desRect, NULL, NULL, flip);
}

void FireWorm::chaseTarget(Player* target) {
	if (!check_death && !global::isPause) {
		if (trackNearestTarget(target)) {
			if (!moveTo(target->getPosition())) {
				if (frameTick > 0) {
					if (frameTick % 5 == 0) {
						if (flip == SDL_FLIP_NONE) {
							SDL_Point p = getPosition();
							p.x+= desRect.w / 2 - 20;
							FireBomb* bomb = new FireBomb(renderer, p, target->getPosition(), { 0,0 }, code);
							global::missles.push_back(bomb);
						}
						else {
							FireBomb* bomb = new FireBomb(renderer, getPosition(), target->getPosition(), { 0,0 }, code);
							global::missles.push_back(bomb);
						}
						//global::missles.push_back(bomb);
					}
					frameTick--;
					return;
				}
				status = ATTACKING;
				frameTick = (*frame)[status].maxFrame;
			}
		}
		else {
			//std::cout << "not found player" << std::endl;
			status = IDLE;
		}
	}
}