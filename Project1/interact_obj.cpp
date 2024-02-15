#include "interact_obj.h"


int Object::getHealth() {
	return stat.health;
}

int Object::getMana() {
	return stat.mana;
}

int Object::getLevel() {
	return stat.level;
}

int Object::getExp() {
	return stat.exp;
}

int Object::getSpeed() {
	return stat.speed;
}

int Object::getRange() {
	return stat.range;
}


int Object::getDamage() {
	return stat.damage;
}

void Object::updateHealth(int newHealth) {
	stat.health = newHealth;
}

void Object::updateMana(int newMana) {
	stat.mana = newMana;
}

void Object::updateLevel(int newLevel) {
	stat.level = newLevel;
}

void Object::updateExp(int newExp) {
	stat.exp = newExp;
}

void Object::updateSpeed(int newSpeed) {
	stat.speed = newSpeed;
}

void Object::updateRange(int newRange) {
	stat.range = newRange;
}

void Object::updateDamage(int newDamage) {
	stat.damage = newDamage;
}

void Object::setClip() {
	wareClips = File::getClips(type);
}

void Object::logicHandle() {
	if (stat.health <= 0) {
		check_death = true;
		status = charState::DEATH;
	}
	//else if (prehealth > stat.health) {
	//	check_take_damage = true;
	//}
	//else {
	//	return;
	//}
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
		}
	}
}

void Object::setProperties() {
	File::getProperties(type, stat);
	texture = TextureManagement::LoadTexture(stat.source, renderer);
}

void Object::render() {
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

	if (status != lastFrame) {
		frameCount = 0;
	}

	srcRect = wareClips[static_cast<int>(status)][change()];
	lastFrame = status;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &desRect, NULL, NULL, flip);
}

int Object::change() {
	switch (status) {
	case charState::IDLE:
		return frameCount / 20;
	case charState::RUNNING:
		return frameCount / 4;
	case charState::ATTACKING:
		return frameCount / 10;
	case charState::DEATH:
		return frameCount / 10;
	}
}

void Object::setLocation() {
	while (collider[map_y][map_x] == 0) {
		map_x = Math::Casuale::casuale(0, w - 1);
		map_y = Math::Casuale::casuale(0, h - 1);
	}

	next_map_x = map_x;
	next_map_y = map_y;

	desRect = { (((map_x - 2) * TILE_WIDTH) + (TILE_WIDTH / 2) + (OBJECT_WIDTH / 2)), ((map_y * TILE_HEIGHT) + TILE_HEIGHT - OBJECT_HEIGHT) - 10, OBJECT_WIDTH, OBJECT_HEIGHT };
}

void Object::init() {
	colliderLoad(water_town);
	setLocation();
	setProperties();
	setClip();
}

