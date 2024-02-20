#include "player.h"

void Player::handleUserEvents(SDL_Event e) {
	if (!check_death && !check_pause) {
		move();
		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
			case SDLK_z:
				check_attack = true;
				status = ATTACKING;
				frameTick = frame[status].maxFrame - 1;
				break;

			case SDLK_a:
			case SDLK_LEFT:
				status = RUNNING;
				flip = SDL_FLIP_HORIZONTAL;
				velo_x = /*-stat.speed_ratio * */-stat.speed;
				break;
			case SDLK_s:
			case SDLK_DOWN:
				status = RUNNING;
				velo_y = /*stat.speed_ratio **/ stat.speed;
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				status = RUNNING;
				flip = SDL_FLIP_NONE;
				velo_x = /*stat.speed_ratio **/ stat.speed;
				break;
			case SDLK_w:
			case SDLK_UP:
				status = RUNNING;
				velo_y = /*-stat.speed_ratio **/ -stat.speed;
				break;
			default:
				break;
			}
		}
		if (e.type == SDL_KEYUP) {
			switch (e.key.keysym.sym) {
			case SDLK_z:
				check_attack = false;
				break;
			case SDLK_a:
			case SDLK_LEFT:
				status = IDLE;
				velo_x = 0;
				//flip = SDL_FLIP_HORIZONTAL;
				isAction = true;
				break;
			case SDLK_s:
			case SDLK_DOWN:
				status = IDLE;
				velo_y = 0;
				isAction = true;
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				status = IDLE;
				velo_x = 0;
				//flip = SDL_FLIP_NONE;
				isAction = true;
				break;
			case SDLK_w:
			case SDLK_UP:
				status = IDLE;
				velo_y = 0;
				isAction = true;
				break;
			default:break;
			}
		}
	}
}

void Player::move() {
	if (/*collisionHandle(collider) && */!check_death && !check_pause) {

		if (frameTick > 0 && status == ATTACKING) {
			frameTick--;
			if (frameTick == 0) status = IDLE;
			return;
		} 

		if (/*collisionHandle(collider) &&*/ velo_x != 0) {
			if (interface->isCameraCollideCornerHorizontal(velo_x) || !interface->isCenterHorizontal(desRect)) {
				desRect.x += velo_x;
			}
			else {
				interface->camera.x += velo_x;
			}
		}

		if (velo_y != 0) {
			if (interface->isCameraCollideCornerVertical(velo_x) || !interface->isCenterVertical(desRect)) {
				desRect.y += velo_y;
			}
			else {
				interface->camera.y += velo_y;
			}
		}
	}
}

void Player::setLocation() {
	map_x = 0;
	map_y = 6;
	desRect = { (((12 - 2) * TILE_WIDTH) + (TILE_WIDTH / 2) + (OBJECT_WIDTH / 2)), ((9 * TILE_HEIGHT) + TILE_HEIGHT - OBJECT_HEIGHT) - 10, OBJECT_WIDTH, OBJECT_HEIGHT };
	interface->cameraInitLocation(map_x, map_y);
	interface->cameraInitObjectLocation(map_x, map_y, desRect);
}