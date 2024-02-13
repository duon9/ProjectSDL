#include "interact_obj.h"


int Object::getHealth() {
	return health;
}

int Object::getMana() {
	return mana;
}

int Object::getLevel() {
	return level;
}

int Object::getExp() {
	return exp;
}

int Object::getSpeed() {
	return speed;
}

int Object::getRange() {
	return range;
}


int Object::getDamage() {
	return damage;
}

void Object::updateHealth(int newHealth) {
	health = newHealth;
}

void Object::updateMana(int newMana) {
	mana = newMana;
}

void Object::updateLevel(int newLevel) {
	level = newLevel;
}

void Object::updateExp(int newExp) {
	exp = newExp;
}

void Object::updateSpeed(int newSpeed) {
	speed = newSpeed;
}

void Object::updateRange(int newRange) {
	range = newRange;
}

void Object::updateDamage(int newDamage) {
	damage = newDamage;
}

void Object::setClip() {
	std::cout << "a" << std::endl;
}

void Object::logicHandle() {
	if (health <= 0) {
		check_death = true;
		status = charState::DEATH;
	}
	else if (prehealth > health) {
		check_take_damage = true;
	}
	else {
		return;
	}
}

bool Object::collisionHandle(std::vector<std::vector<int>> collider) {
	//std::cout << next_map_x << " " << next_map_y << std::endl;
	if (next_map_x >= w || next_map_x < 0 || next_map_y >= h || next_map_y < 0) {
		frameTick = 0;
		check_run = false;
		status = charState::IDLE;
		next_map_x = map_x;
		next_map_y = map_y;
		*orient = { 0,0,0,0 };
		return false;
	}
	
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

	//std::cout << map_x << " " << map_y << std::endl;

	return true;
}

void Object::colliderLoad(std::string path) {
	collider = File::readCollision(path);
	this->w = collider[0].size();
	this->h = collider.size();
}

void Object::move() {
	if (collisionHandle(collider) && !check_death && !check_pause) {
		if (frameTick % 5 == 0) {
			if (orient->left && check_run) {
				desRect.x -= PLAYER_SPEED;
			}
			else if (orient->down && check_run) {
				desRect.y += PLAYER_SPEED;
			}
			else if (orient->right && check_run) {
				desRect.x += PLAYER_SPEED;
			}
			else if (orient->up && check_run) {
				desRect.y -= PLAYER_SPEED;
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

void Object::render() {
	lastFrame = newFrame;

	if (direction) {
		flip = SDL_FLIP_HORIZONTAL;
	}
	else {
		flip = SDL_FLIP_NONE;
	}

	if (frameCount == MAX_IDLE_FRAMECOUNT && status == charState::IDLE) {
		frameCount = 0;
	}
	else if (frameCount == MAX_RUN_FRAMECOUNT && status == charState::RUNNING) {
		frameCount = 0;
	}
	else if (frameCount == MAX_ATTACK_FRAMECOUNT && status == charState::ATTACKING) {
		frameCount = 0;
	}
	else if (frameCount == MAX_DEAD_FRAMECOUNT && status == charState::DEATH) {
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

		srcRect = runFrame[frameCount / 4];
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

		srcRect = deathFrame[frameCount / 10];

		if (frameCount == 98) {
			frameCount--;
		}

		break;
	}

	SDL_RenderCopyEx(renderer, texture, &srcRect, &desRect, NULL, NULL, flip);
}