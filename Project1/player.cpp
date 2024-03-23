#include "player.h"

#define check (!orient.up && !orient.down && !orient.left && !orient.right)

SDL_Texture* Player::vessel = nullptr;

void Player::handleUserEvents(SDL_Event *e) {
	if (!check_death && !check_pause) {
		move();
		if (e->type == SDL_KEYDOWN) {
			switch (e->key.keysym.sym) {
			case SDLK_z:

				if (status == RUNNING) return;
				if (frameTick > 0) return;
				status = ATTACKING;
				//frameTick = frame[status].maxFrame - 1;
				attackSound->play();
				attack();
				break;
			case SDLK_x:
				if (!isInvisible) {
					SDL_SetTextureAlphaMod(texture, 100);
					isInvisible = true;
				}
				else {
					SDL_SetTextureAlphaMod(texture, 255);
					isInvisible = false;
				}
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
				if (orient.right == 1 || status == ATTACKING || frameTick > 0) return;
				if (lastStatus != RUNNING) runSound->play();
				orient.left = 1;
				status = RUNNING;
				flip = SDL_FLIP_HORIZONTAL;
				velo_x = -1;
				break;
			case SDLK_s:
			case SDLK_DOWN:
				if (orient.up == 1 || status == ATTACKING || frameTick > 0) return;
				if (lastStatus != RUNNING) runSound->play();
				orient.down = 1;
				status = RUNNING;
				velo_y = 1;
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				if (orient.left == 1 || status == ATTACKING || frameTick > 0) return;
				if (lastStatus != RUNNING) runSound->play();
				orient.right = 1;
				status = RUNNING;
				flip = SDL_FLIP_NONE;
				velo_x = 1;
				break;
			case SDLK_w:
			case SDLK_UP:
				if (orient.down == 1 || status == ATTACKING || frameTick > 0) return;
				if (lastStatus != RUNNING) runSound->play();
				orient.up = 1;
				status = RUNNING;
				velo_y = -1;
				break;
			default:
				break;
			}
		}
		if (e->type == SDL_KEYUP) {
			switch (e->key.keysym.sym) {
			case SDLK_LSHIFT:
				stat.speed /= 2;
				break;
			case SDLK_a:
			case SDLK_LEFT:
				//status = IDLE;
				runSound->stop();
				velo_x = 0;
				orient.left = 0;
				//velo_x = 0;
				//flip = SDL_FLIP_HORIZONTAL;
				break;
			case SDLK_s:
			case SDLK_DOWN:
				//status = IDLE;
				runSound->stop();
				orient.down = 0;
				velo_y = 0;
		
				//velo_y = 0;
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				//status = IDLE;
				//velo_x = 0;
				runSound->stop();
				orient.right = 0;
				velo_x = 0;
				break;
			case SDLK_w:
			case SDLK_UP:
				//status = IDLE;
				runSound->stop();
				orient.up = 0;
				velo_y = 0;
				//velo_y = 0;
				break;
			default:break;
			}
		}

		if (e->type == SDL_MOUSEMOTION) {
			if (e->motion.x > desRect.x + desRect.w / 2) flip = SDL_FLIP_NONE;
			else flip = SDL_FLIP_HORIZONTAL;
		}

		if (e->type == SDL_MOUSEBUTTONDOWN) {
			if (e->button.button == SDL_BUTTON_LEFT) {
				if (status == RUNNING) return;
				if (frameTick > 0) return;
				status = ATTACKING;
				//frameTick = frame[status].maxFrame - 1;
				attackSound->play();
				attack();
			}
			if (e->button.button == SDL_BUTTON_RIGHT) {
				WaterBall* ball = new WaterBall(renderer, getPosition(), getCursorPosition(e), code);
				global::missles.push_back(ball);
			}
		}

		if (check && frameTick == 0) status = IDLE;
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
			if (frameTick == 0) {
				status = IDLE;
				attackSound->stop();
			};
			return;
		} 
		else if ((velo_x != 0 || velo_y != 0) && frameTick == 0) {
			Math::Vector v = Math::Vector(velo_x, velo_y);
			v.normalize();
			velo_x = v.getX() * stat.speed;
			velo_y = v.getY() * stat.speed;
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
}

void Player::setLocation() {
	map_x = 1;
	map_y = 1;
	//setSize(64, 64);
	interface->cameraInitLocation(map_x, map_y);
	interface->cameraInitObjectLocation(map_x, map_y, desRect);
	position.x = interface->camera.x + desRect.x;
	position.y = interface->camera.y + desRect.y;
}

void Player::setLocation(int x, int y) {
	map_x = x / TILE_WIDTH;
	map_y = y / TILE_HEIGHT;
	//setSize(64, 64);
	interface->cameraInitLocation(map_x, map_y);
	interface->cameraInitObjectLocation(map_x, map_y, desRect);
	position.x = interface->camera.x + desRect.x;
	position.y = interface->camera.y + desRect.y;
}

void Player::setCollision() {
	//collider = File::readCollision(path);
	collision = new Collision(Object::collider, &desRect, &interface->camera, &position);
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

void Player::setSFX() {
	attackSound->add("assets/audio/player-attack.wav");
	runSound->add("assets/audio/run.mp3");
}

void Player::init() {
	setAbility();
	setSize(54, 54);
	setSFX();
	setProtocolCode();
	setProtocol();
	setLocation();
	setProperties();
	setBarProperties();
	setClip();
	setFrameLimit();
	setCollision();
}

void Player::setBarProperties() {
	interface->mana_display->setProperties(stat.mana);
	interface->health_display->setProperties(stat.health);
}

void Player::reload() {
	collision->reload(Object::collider);
	setLocation(0, 6 * 32);
}

void Player::draw() {
	SDL_RenderCopyEx(renderer, Player::vessel, &srcRect, &desRect, NULL, NULL, flip);
}

void Player::setAbility() {
	WaterBall::loadClips();
	WaterBall::loadTexture(renderer);
}

SDL_Point Player::getCursorPosition(SDL_Event* e) {
	return { e->motion.x + interface->camera.x, e->motion.y + interface->camera.y };
}