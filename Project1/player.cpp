#include "player.h"

void Player::handleUserEvents(SDL_Event e) {
	if (!check_death && !check_pause) {
		if (frameCount > 0) {
			move();
			frameCount--;
			return;
		}
		else if (frameTick == 0 && check_run == true) {
			status = charState::RUNNING;
			frameCount = RUN_FRAMETICK;
			//*orient = { 0,0,0,0 };
		}
		else if (frameTick == 0 && !check_run) {
			status = charState::IDLE;
			//*orient = { 0,0,0,0 };
			switch (e.type) {
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym) {
				case SDLK_z:
					frameTick = ATTACK_FRAMETICK;
					check_attack = true;
					status = charState::ATTACKING;
					break;

					/*
					* TODO: add check orient in case keyPressed and reset the reversed orient to zero
					*/
				case SDLK_a:
				case SDLK_LEFT:
					status = charState::RUNNING;
					frameTick = RUN_FRAMETICK;
					check_run = true;
					orient->left = 1;
					flip = SDL_FLIP_HORIZONTAL;
					next_map_x = map_x - 1;
					//keyPressed = true;
					break;
				case SDLK_d:
				case SDLK_RIGHT:
					status = charState::RUNNING;
					frameTick = RUN_FRAMETICK;
					check_run = true;
					orient->right = 1;
					flip = SDL_FLIP_NONE;
					next_map_x = map_x + 1;
					//keyPressed = true;

					break;

				case SDLK_w:
				case SDLK_UP:
					status = charState::RUNNING;
					frameTick = RUN_FRAMETICK;
					check_run = true;
					orient->up = 1;
					next_map_y = map_y - 1;
					//keyPressed = true;

					break;

				case SDLK_s:
				case SDLK_DOWN:
					status = charState::RUNNING;
					frameTick = RUN_FRAMETICK;
					check_run = true;
					orient->down = 1;
					next_map_y = map_y + 1;
					//keyPressed = true;

					break;
				}

				//next_status = status;
				break;
			case SDL_KEYUP:
				switch (e.key.keysym.sym) {
				case SDLK_a:
				case SDLK_LEFT:
					check_run = false;
					*orient = { 0,0,0,0 };
					break;
					//next_status = charState::IDLE;
				case SDLK_s:
				case SDLK_DOWN:
					//next_status = charState::IDLE;
					check_run = false;
					*orient = { 0,0,0,0 };
					break;
				case SDLK_d:
				case SDLK_RIGHT:
					//next_status = charState::IDLE;
					check_run = false;
					*orient = { 0,0,0,0 };
					break;
				case SDLK_w:
				case SDLK_UP:
					//next_status = charState::IDLE;
					check_run = false;
					*orient = { 0,0,0,0 };
					break;
				}
				//*orient = { 0,0,0,0 };
				break;
			}
		}
	}
	else {
		std::cout << "vla" << std::endl;
		return;
	}
}

void Player::move() {
	if (/*collisionHandle(collider) && */!check_death && !check_pause) {
		if (frameTick % 5 == 0) {
			if (orient->left && check_run) {
				/*desRect.x -= PLAYER_SPEED;*/
				interface->srcRect.x -= stat.speed;
			}
			else if (orient->down && check_run) {
				/*desRect.y += PLAYER_SPEED;*/
				interface->srcRect.y += stat.speed;
			}
			else if (orient->right && check_run) {
				/*desRect.x += PLAYER_SPEED;*/
				interface->srcRect.x += stat.speed;
			}
			else if (orient->up && check_run) {
				/*desRect.y -= PLAYER_SPEED;*/
				interface->srcRect.y -= stat.speed;
			}
		}
	}
}