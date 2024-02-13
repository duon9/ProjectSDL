#include "player.h"

void Player::init() {
	updateHealth(PLAYER_HEALTH);
	updateMana(PLAYER_MANA);
	updateLevel(PLAYER_LEVEL);

	collider = File::readCollision(water_town);

	map_x = 0;
	map_y = 2;

	next_map_x = map_x;
	next_map_y = map_y;

	setClip();
	texture = TextureManagement::LoadTexture(source, renderer);

	desRect = { (((map_x - 2) * TILE_WIDTH) + (TILE_WIDTH / 2) + (OBJECT_WIDTH / 2) ), ((map_y* TILE_HEIGHT) + TILE_HEIGHT - OBJECT_HEIGHT) - 10, OBJECT_WIDTH, OBJECT_HEIGHT};
	srcRect = { 0 , 0, 0 ,0 };
}

/**
* @brief 
* @param
*/

void Player::render() {
	lastFrame = newFrame;

	if (direction) {
		flip = SDL_FLIP_HORIZONTAL;
	}
	else {
		flip = SDL_FLIP_NONE;
	}

	if (frameCount == 200 - 1 && status == charState::IDLE) {
		frameCount = 0;
	}
	else if (frameCount == 80 - 1 && status == charState::RUNNING) {
		frameCount = 0;
	}
	else if (frameCount == 100 - 1 && status == charState::ATTACKING) {
		frameCount = 0;
	}

	frameCount++;

	switch (status) {
	case charState::IDLE:
		newFrame = charState::IDLE;
		if (lastFrame != newFrame) {
			frameCount = 0;
		}

		srcRect = idleFrame[frameCount / 20];
		
		break;
	case charState::RUNNING:
		newFrame = charState::RUNNING;
		if (lastFrame != newFrame) {
			frameCount = 0;
		}

		srcRect = runFrame[frameCount / 8];
		break;
	case charState::ATTACKING:
		newFrame = charState::ATTACKING;

		if (lastFrame != newFrame) {
			frameCount = 0;
		}

		srcRect = attackFrame[frameCount / 10];
		break;

	case charState::DEATH:
		newFrame = charState::DEATH;
		if (lastFrame != newFrame) {
			frameCount = 0;
		}


	}




	SDL_RenderCopyEx(renderer, texture, &srcRect, &desRect, NULL, NULL, flip);
}

void Player::setClip() {
	if (source == ROGUE) {
		for (int i = 0; i < 10; i++) {
			idleFrame[i] = { i * 32, 0, 32,32 };
			runFrame[i] = { i * 32, 2 * 32 ,32, 32 };
			attackFrame[i] = { i * 32, 3 * 32, 32, 32 };
			spellcastFrame[i] = { i * 32, 1 * 32, 32, 32 };
			deathFrame[i] = { i * 32, 4 * 32, 32, 32 };
		}
	}
	else if (source == littleboy) {
		for (int i = 0; i < 6; i++) {
			idleFrame[i] = { i * 48, 0, 48, 48 };
			runFrame[i] = { i * 48, 1 * 48 ,48, 48 };
			attackFrame[i] = { i * 48, 2 * 48, 48, 48 };
			deathFrame[i] = { i * 48, 4 * 48, 48, 48 };
		}
	}
}

void Player::handleUserEvents(SDL_Event e) {
	if (check_death == false) {
		if (frameTick > 0 && (check_run == true || check_attack == true)) {
			move();
			frameTick--;
			return;
		}
		else if (frameTick == 0 && (check_run == true || check_attack == true)) {
			check_run = false;
			check_attack = false;
			status = next_status;
			orient->down = 0;
			orient->left = 0;
			orient->up = 0;
			orient->right = 0;
		}
		else if (!check_run || !check_attack) {
			switch (e.type) {
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym) {
				case SDLK_z:
					frameTick = 100;
					check_attack = true;
					status = charState::ATTACKING;
					health -= 500;
					break;
				case SDLK_a:
				case SDLK_LEFT:
					status = charState::RUNNING;
					frameTick = 80;
					check_run = true;
					orient->left = 1;
					direction = true;
					next_map_x = map_x - 1;
					break;
				case SDLK_d:
				case SDLK_RIGHT:
					status = charState::RUNNING;
					frameTick = 80;
					check_run = true;
					orient->right = 1;
					direction = false;
					next_map_x = map_x + 1;
					break;

				case SDLK_w:
				case SDLK_UP:
					status = charState::RUNNING;
					frameTick = 80;
					check_run = true;
					orient->up = 1;
					next_map_y = map_y - 1;
					break;

				case SDLK_s:
				case SDLK_DOWN:
					status = charState::RUNNING;
					frameTick = 80;
					check_run = true;
					orient->down = 1;
					next_map_y = map_y + 1;
					break;
				}
				break;
			case SDL_KEYUP:
				switch (e.key.keysym.sym) {
				case SDLK_a:
				case SDLK_LEFT:
					next_status = charState::IDLE;
				case SDLK_s:
				case SDLK_DOWN:
					next_status = charState::IDLE;
				case SDLK_d:
				case SDLK_RIGHT:
					next_status = charState::IDLE;
				case SDLK_w:
				case SDLK_UP:
					next_status = charState::IDLE;
				}
				break;
			default:
				next_status = charState::IDLE;
				break;
			}
		}
	}
	else {
		return;
	}
}

void Player::move() {
	if (collisionHandle(collider)) {
		if (frameTick % 10 == 0) {
			if (orient->left && check_run) {
				desRect.x -= 32.0 / 8;
			}
			else if (orient->down && check_run) {
				desRect.y += 32.0 / 8;
			}
			else if (orient->right && check_run) {
				desRect.x += 32.0 / 8;
			}
			else if (orient->up && check_run) {
				desRect.y -= 32.0 / 8;
			}
			else if (orient->left && orient->up && check_run) {
				desRect.x -= 32.0 / 10;
				desRect.y -= 32.0 / 10;
			}
			else if (orient->left && orient->down && check_run) {
				desRect.x -= 32.0 / 10;
				desRect.y += 32.0 / 10;
			}
			else if (orient->right && orient->up && check_run) {
				desRect.x += 32.0 / 10;
				desRect.y -= 32.0 / 10;
			}
			else if (orient->right && orient->down && check_run) {
				desRect.x += 32.0 / 10;
				desRect.y += 32.0 / 10;
			}
			else {
				return;
			}
		}
		else {
			return;
		}
	}
	else {
		return;
	}
}

bool Player::collisionHandle(std::vector<std::vector<int>> collider) {
	if (collider[next_map_y][next_map_x] == 0) {
		frameTick = 0; 
		check_run = false;
		status = charState::IDLE;
		next_map_x = map_x;
		next_map_y = map_y;
		*orient = { 0,0,0,0 };
		return false;
	}
	map_x = next_map_x;
	map_y = next_map_y;
	return true;
}