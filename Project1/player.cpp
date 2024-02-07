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

	if (frameCount == 200 && status == charState::IDLE) {
		frameCount = 0;
	}
	else if (frameCount == 50 && status == charState::RUNNING) {
		frameCount = 0;
	}
	else if (frameCount == 100 && status == charState::ATTACKING) {
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

		srcRect = runFrame[frameCount / 5];

		if (orient->right == 1 && orient->left == 0) {
			flip = SDL_FLIP_NONE;
		}
		else if (orient->left == 1 && orient->right == 0) {
			flip = SDL_FLIP_HORIZONTAL;
		}
		break;
	case charState::ATTACKING:
		newFrame = charState::ATTACKING;

		if (lastFrame != newFrame) {
			frameCount = 0;
		}

		srcRect = attackFrame[frameCount / 10];

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
		if (frameTick > 0) {
			std::cout << "frameTick: " << frameTick << std::endl;
			frameTick--;
			return;
		}
		else {
			switch (e.type) {
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym) {
				case SDLK_z:
					status = charState::ATTACKING;
					frameTick = 100;
					std::cout << "attacking \n";
					break;
				case SDLK_x:
					status = charState::CASTING;
					break;
				case SDLK_w:
				case SDLK_UP:
					status = charState::RUNNING;
					orient->up = 1;
					//if (frameCount % 5 == 0) desRect.y -= PLAYER_SPEED;
					//std::cout << "key up pressed\n";
					frameTick = 50;
					break;

				case SDLK_a:
				case SDLK_LEFT:
					status = charState::RUNNING;
					orient->left = 1;
					//if (frameCount % 5 == 0) desRect.x -= PLAYER_SPEED;
					//std::cout << "key left pressed\n";
					frameTick = 50;
					break;


				case SDLK_s:
				case SDLK_DOWN:
					status = charState::RUNNING;
					orient->down = 1;
					//if (frameCount % 5 == 0) desRect.y += PLAYER_SPEED;
					//std::cout << "key down pressed\n";
					frameTick = 50;
					break;

				case SDLK_d:
				case SDLK_RIGHT:
					status = charState::RUNNING;
					orient->right = 1;
					//if (frameCount % 5 == 0) desRect.x += PLAYER_SPEED;
					//std::cout << "key right pressed\n";
					frameTick = 50;
					break;

				}
				break;
			case SDL_KEYUP:
				switch (e.key.keysym.sym) {
				case SDLK_w:
				case SDLK_UP:
					orient->up = 0;
					//std::cout << "key up released\n";
					break;

				case SDLK_a:
				case SDLK_LEFT:
					orient->left = 0;
					//std::cout << "key left released\n";
					break;
				case SDLK_s:
				case SDLK_DOWN:
					orient->down = 0;
					//std::cout << "key down released\n";
					break;
				case SDLK_d:
				case SDLK_RIGHT:
					orient->right = 0;
					//std::cout << "key right released\n";
					break;
				}
				status = charState::IDLE;
				break;
			}
		}
		/*
		switch (e.type) {
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym) {
			case SDLK_z:
				status = charState::ATTACKING;
				frameTick = 100;
				break;
			case SDLK_x:
				status = charState::CASTING;
				break;
			case SDLK_w:
			case SDLK_UP:
				status = charState::RUNNING;
				orient->up = 1;
				if (frameCount % 5 == 0) desRect.y -= PLAYER_SPEED;
				//std::cout << "key up pressed\n";
				break;
					
			case SDLK_a:
			case SDLK_LEFT:
				status = charState::RUNNING;
				orient->left = 1;
				if (frameCount % 5 == 0) desRect.x-= PLAYER_SPEED;
				//std::cout << "key left pressed\n";
				break;

					
			case SDLK_s:
			case SDLK_DOWN:
				status = charState::RUNNING;
				orient->down = 1;
				if (frameCount % 5 == 0) desRect.y+=PLAYER_SPEED;
				//std::cout << "key down pressed\n";
				break;
					
			case SDLK_d:
			case SDLK_RIGHT:
				status = charState::RUNNING;
				orient->right = 1;
				if (frameCount % 5 == 0) desRect.x+= PLAYER_SPEED;
				//std::cout << "key right pressed\n";
				
				break;
					
			}
			break;
		case SDL_KEYUP:
			switch (e.key.keysym.sym) {
			case SDLK_w:
			case SDLK_UP:
				orient->up = 0;
				//std::cout << "key up released\n";
				break;
					
			case SDLK_a:
			case SDLK_LEFT:
				orient->left = 0;
				//std::cout << "key left released\n";
				break;
			case SDLK_s:
			case SDLK_DOWN:
				orient->down = 0;
				//std::cout << "key down released\n";
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				orient->right = 0;
				//std::cout << "key right released\n";
				break;
			}
			status = charState::IDLE;
			break;
		}
		*/
	}
	else {
		status = charState::DEATH;
		std::cout << "Error D102" << std::endl;
	}
}