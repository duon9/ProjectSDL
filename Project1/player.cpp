#include "player.h"

void Player::handleUserEvents(SDL_Event e) {
	if (!check_death && !check_pause) {
		if (frameTick > 0 && (check_run == true || check_attack == true)) {
			move();
			frameTick--;
			return;
		}
		else if (frameTick == 0 && (check_run == true || check_attack == true)) {
			check_run = false;
			check_attack = false;
			/*if (!keyPressed) {
				status = next_status;
			}*/

			status = next_status;
			*orient = { 0,0,0,0 };
		}
		else if (!check_run || !check_attack) {
			switch (e.type) {
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym) {
				case SDLK_z:

					//if (mana <= 0) {
					//	return;
					//}
					frameTick = ATTACK_FRAMETICK;
					check_attack = true;
					status = charState::ATTACKING;
					//health -= 500;
					//mana -= 1;
					break;
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
			}
		}
	}
	else {
		return;
	}
}
