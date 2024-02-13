#include "computer.h"
#include "math.h"

void Computer::init() {

	map_x = 10;
	map_y = 2;
	colliderLoad(water_town);

	/*for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			std::cout << collider[i][j] << std::endl;
		}
	}*/

	next_map_x = map_x;
	next_map_y = map_y;

	setClip();
	texture = TextureManagement::LoadTexture(type, renderer);

	if (texture == nullptr) std::cout << "Computer class - texture not found \n";
	desRect = { (((map_x - 2) * TILE_WIDTH) + (TILE_WIDTH / 2) + (OBJECT_WIDTH / 2)), ((map_y * TILE_HEIGHT) + TILE_HEIGHT - OBJECT_HEIGHT) - 10, OBJECT_WIDTH, OBJECT_HEIGHT };
	srcRect = { 0 , 0, 0 ,0 };
}

void Computer::setClip() {
	if (type == littleboy) {
		for (int i = 0; i < 6; i++) {
			idleFrame[i] = { i * 48, 0, 48, 48 };
			runFrame[i] = { i * 48, 1 * 48 ,48, 48 };
			attackFrame[i] = { i * 48, 2 * 48, 48, 48 };
			deathFrame[i] = { i * 48, 4 * 48, 48, 48 };
		}
	}
	else if (type == VIKING) {
		for (int i = 0; i < 10; i++) {
			idleFrame[i] = {i * 32, 0, 32, 32};
		}
	}
	else if (type == ROGUE) {
		for (int i = 0; i < 10; i++) {
			idleFrame[i] = { i * 32, 0, 32,32 };
			runFrame[i] = { i * 32, 2 * 32 ,32, 32 };
			attackFrame[i] = { i * 32, 3 * 32, 32, 32 };
			spellcastFrame[i] = { i * 32, 1 * 32, 32, 32 };
			deathFrame[i] = { i * 32, 4 * 32, 32, 32 };
		}
	}
	else if (type == DARK) {
		for (int i = 0; i < 8; i++) {
			idleFrame[i] = { i * 250, 0, 250, 250 };
		}
	}
}

//void Computer::render() {
//
//	frameCount++;
//	if (frameCount == 79) {
//		frameCount = 0;
//	}
//
//	switch (status) {
//	case charState::IDLE:
//		srcRect = idleFrame[frameCount / 10];
//	}
//	SDL_RenderCopyEx(renderer, texture, &srcRect, &desRect, NULL, NULL, flip);
//}

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
				*orient = { 0,0,0,0 };
				status = charState::IDLE;
			}
			else if (!check_run && !check_attack) {
				if (Math::Casuale::casuale(0, 100) == 5) {
					std::cout << map_x << " " << map_y << std::endl;
					int directionIndex = Math::Casuale::casuale(0, 3);
					std::cout << directionIndex << std::endl;
					switch (directionIndex) {
					case UP:
						status = charState::RUNNING;
						frameTick = RUN_FRAMETICK;
						check_run = true;
						orient->up = 1;
						next_map_y = map_y - 1;
						break;
					case DOWN:
						status = charState::RUNNING;
						frameTick = RUN_FRAMETICK;
						check_run = true;
						orient->down = 1;
						next_map_y = map_y + 1;
						break;
					case LEFT:
						status = charState::RUNNING;
						frameTick = RUN_FRAMETICK;
						check_run = true;
						orient->left = 1;
						direction = true;
						next_map_x = map_x - 1;
						break;
					case RIGHT:
						status = charState::RUNNING;
						frameTick = RUN_FRAMETICK;
						check_run = true;
						orient->right = 1;
						direction = false;
						next_map_x = map_x + 1;
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