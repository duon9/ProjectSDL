#include "player.h"

void Player::handleUserEvents(SDL_Event *e) {
	if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_r) {
		check_death = false;
		status = IDLE;
		setProperties();
	}
	if (!check_death && !check_pause) {
		move();

		if (e->type == SDL_KEYDOWN) {
			switch (e->key.keysym.sym) {
			case SDLK_z:

				if (status == RUNNING) return;
				if (frameTick > 0) return;
				status = ATTACKING;
				//frameTick = frame[status].maxFrame - 1;
				attack();
				break;
			case SDLK_x:
				SDL_SetTextureAlphaMod(texture, 100);
				isInvisible = true;
				break;
			case SDLK_c:
				SDL_SetTextureAlphaMod(texture, 255);
				isInvisible = false;
				//std::cout << status << std::endl;
				//std::cout << frameTick << std::endl;
				break;
			case SDLK_v:
				SDL_Point porn = getPosition();
				std::cout << porn.x << " " << porn.y;
				break;
			case SDLK_b:
				Global::gamestate = MENU;
				break;
			case SDLK_r:
				check_death = false;
				status = IDLE;
				setProperties();
				break;

			case SDLK_LSHIFT:
				stat.speed = 4;
				//stat.mana -= 1;
				break;
			case SDLK_a:
			case SDLK_LEFT:
				status = RUNNING;
				flip = SDL_FLIP_HORIZONTAL;
				velo_x = 1 * -stat.speed;
				break;
			case SDLK_s:
			case SDLK_DOWN:
				status = RUNNING;
				velo_y = 1 * stat.speed;
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				status = RUNNING;
				flip = SDL_FLIP_NONE;
				velo_x = 1 * stat.speed;
				break;
			case SDLK_w:
			case SDLK_UP:
				status = RUNNING;
				velo_y = 1 * -stat.speed;
				break;
			default:
				break;
			}
		}
		if (e->type == SDL_KEYUP) {
			switch (e->key.keysym.sym) {
			case SDLK_z:
				//check_attack = false;
				break;
			case SDLK_LSHIFT:
				stat.speed /= 2;
				break;
			case SDLK_a:
			case SDLK_LEFT:
				status = IDLE;
				velo_x = 0;
				//flip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_s:
			case SDLK_DOWN:
				status = IDLE;
				velo_y = 0;
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				status = IDLE;
				velo_x = 0;
				//flip = SDL_FLIP_NONE;
				break;
			case SDLK_w:
			case SDLK_UP:
				status = IDLE;
				velo_y = 0;
				break;
			default:break;
			}
		}
	}
}

void Player::move() {
	if (/*collisionHandle(collider) && */!check_death && !check_pause) {
		// TODO: found some problem here
		if (isInvisible == true) {
			if (stat.mana <= 0) {
				isInvisible = false;
				SDL_SetTextureAlphaMod(texture, 255);
			}
			else {
				stat.mana -= 1;
			}
			//stat.mana -= 2;
		}

		if (frameTick > 0) {
			frameTick--;
			if (frameTick == 0) status = IDLE;
			return;
		} 
		if (!collision->isColliding(velo_x, velo_y)) {

			if (velo_x != 0) {
				position.x += velo_x;
				if (interface->isCameraCollideCornerHorizontal(velo_x) || !interface->isCenterHorizontal(desRect)) {
					desRect.x += velo_x;
				}
				else {
					interface->camera.x += velo_x;
				}
			}

			if (velo_y != 0) {
				position.y += velo_y;
				if (interface->isCameraCollideCornerVertical(velo_y) || !interface->isCenterVertical(desRect)) {
					desRect.y += velo_y;
				}
				else {
					interface->camera.y += velo_y;
				}
			}
		}
	}
}

void Player::setLocation() {
	map_x = 0;
	map_y = 6;
	desRect = { (((12 - 2) * TILE_WIDTH) + (TILE_WIDTH / 2) + (OBJECT_WIDTH / 2)), ((9 * TILE_HEIGHT) + TILE_HEIGHT - OBJECT_HEIGHT) - 10, 52, 52};
	interface->cameraInitLocation(map_x, map_y);
	interface->cameraInitObjectLocation(map_x, map_y, desRect);
	position.x = interface->camera.x + desRect.x;
	position.y = interface->camera.y + desRect.y;
}

void Player::setCollision(std::string path) {
	collider = File::readCollision(path);
	collision = new Collision(collider, &desRect, &interface->camera, &position);
}

void Player::setProtocolCode() {
	code = ALLY_CODE;
}

void Player::handleBarDisplay() {
	interface->mana_display->updateProperties(stat.mana);
	interface->mana_display->updateBar();

	interface->health_display->updateProperties(stat.health);
	interface->health_display->updateBar();
}

void Player::init() {
	setProtocolCode();
	setProtocol();
	setLocation();
	setProperties();
	setBarProperties();
	setClip();
	setFrameLimit();
	setCollision(water_town);
}

void Player::setBarProperties() {
	interface->mana_display->setProperties(stat.mana);
	interface->health_display->setProperties(stat.health);
}