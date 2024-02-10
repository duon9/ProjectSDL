#include "computer.h"

void Computer::init() {
	setClip();
	srcRect = { 0, 0, 0 ,0 };
	desRect = { 32 * 3, 32 * 3, 128, 128 };
	texture = TextureManagement::LoadTexture(type, renderer);

	if (texture == nullptr) std::cout << "Computer class - texture not found \n";

	status = charState::IDLE;
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

void Computer::render() {

	frameCount++;
	if (frameCount == 79) {
		frameCount = 0;
	}

	switch (status) {
	case charState::IDLE:
		srcRect = idleFrame[frameCount / 10];
	}
	SDL_RenderCopyEx(renderer, texture, &srcRect, &desRect, NULL, NULL, flip);
}