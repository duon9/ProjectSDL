#include "player.h"

void Player::init() {

	updateHealth(PLAYER_HEALTH);
	updateMana(PLAYER_MANA);
	updateLevel(PLAYER_LEVEL);
	updateArmor(PLAYER_ARMOR);

	setClip();
	texture = TextureManagement::LoadTexture(source, renderer);

	desRect = { 32, 32, static_cast<int>(32 * 2), static_cast<int>(32 * 2) };
	srcRect = { 0 , 0, 0 ,0 };

}

void Player::render() {

	lastFrame = newFrame;

	frameCount++;
	if (frameCount == 200) {
		frameCount = 0;
	}

	frameTick = frameCount / 20;
	frameMove = frameCount % 10;

	switch (status) {
	case charState::IDLE:
		newFrame = charState::IDLE;
		if (lastFrame != newFrame) {
			frameCount = 0;
		}

		srcRect = idleFrame[frameTick];

		if (orient->right == 1 && orient->left == 0) {
			flip = SDL_FLIP_NONE;
		}
		else if (orient->left == 1 && orient->right == 0) {
			flip = SDL_FLIP_HORIZONTAL;
		}
		break;
	case charState::RUNNING:
		newFrame = charState::RUNNING;
		if (lastFrame != newFrame) {
			frameCount = 0;
		}

		srcRect = runFrame[frameTick];

		if (orient->right == 1 && orient->left == 0) {
			flip = SDL_FLIP_NONE;
		}
		else if (orient->left == 1 && orient->right == 0) {
			flip = SDL_FLIP_HORIZONTAL;
		}
		break;
	}

	SDL_RenderCopyEx(renderer, texture, &srcRect, &desRect, NULL, NULL, flip);
}

void Player::setClip() {
	if (true) {
		for (int i = 0; i < 10; i++) {
			idleFrame[i] = { i * 32, 0, 32,32 };
			runFrame[i] = { i * 32, 2 * 32 ,32, 32 };
			attackFrame[i] = { i * 32, 3 * 32, 32, 32 };
			spellcastFrame[i] = { i * 32, 1 * 32, 32, 32 };
			deathFrame[i] = { i * 32, 4 * 32, 32, 32 };
		}
	}
}

void Player::handleUserEvents(SDL_Event e) {
	if (check_death == false) {
		if (SDL_PollEvent(&e) != 0) {
			switch (e.type) {
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym) {
				case SDLK_z:
					status = charState::ATTACKING;
					break;
				case SDLK_x:
					status = charState::CASTING;
					break;
				case SDLK_w:
				case SDLK_UP:
					status = charState::RUNNING;
					orient->up = 1;
					desRect.y--;
					break;
				case SDLK_a:
				case SDLK_LEFT:
					status = charState::RUNNING;
					orient->left = 1;
					desRect.x--;
					break;
				case SDLK_s:
				case SDLK_DOWN:
					status = charState::RUNNING;
					orient->down = 1;
					desRect.y++;
					break;
				case SDLK_d:
				case SDLK_RIGHT:
					status = charState::RUNNING;
					orient->right = 1;
					desRect.x++;
					break;
				}
			case SDL_KEYUP:
				switch (e.key.keysym.sym) {
				case SDLK_w:
				case SDLK_UP:
					status = charState::IDLE;
					orient->up = 0;
					break;
				case SDLK_a:
				case SDLK_LEFT:
					status = charState::IDLE;
					orient->left = 0;
					break;
				case SDLK_s:
				case SDLK_DOWN:
					status = charState::IDLE;
					orient->down = 0;
					break;
				case SDLK_d:
				case SDLK_RIGHT:
					status = charState::IDLE;
					orient->right = 0;
					break;
				}
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