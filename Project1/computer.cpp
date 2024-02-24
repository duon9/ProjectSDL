#include "computer.h"
#include "math.h"

void Computer::randomBotMovement() {
	if (!check_death && !check_pause) {
		if (find_enemy) {
			return;
		}
		else {

			if (frameTick > 0 && (check_run || check_attack)) {
				move();
				frameTick--;
				return;
			}
			else if (frameTick == 0 && (check_run || check_attack)) {
				check_run = false;
				check_attack = false;
				status = charState::IDLE;
			}
			else if (!check_run && !check_attack) {
				if (Math::Casuale::casuale(0, 100) == 5) {
					//std::cout << map_x << " " << map_y << std::endl;
					int directionIndex = Math::Casuale::casuale(0, 3);
					//std::cout << directionIndex << std::endl;
					switch (directionIndex) {
					case UP:
						status = charState::RUNNING;
						frameTick = RUN_FRAMETICK;
						check_run = true;
						break;
					case DOWN:
						status = charState::RUNNING;
						frameTick = RUN_FRAMETICK;
						check_run = true;
						break;
					case LEFT:
						status = charState::RUNNING;
						frameTick = RUN_FRAMETICK;
						check_run = true;
						flip = SDL_FLIP_HORIZONTAL;
						break;
					case RIGHT:
						status = charState::RUNNING;
						frameTick = RUN_FRAMETICK;
						check_run = true;
						flip = SDL_FLIP_NONE;
						break;
					default:
						break;
					}
				}
				else {
					return;
				}
			}
			else {
				std::cout << "Error 203 \n";
				return;
			}
		}
	} 
}