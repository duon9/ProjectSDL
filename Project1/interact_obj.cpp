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
}

void Object::collisionHandle() {
	
}

void Object::setCollision(std::string path) {
	collider = File::readCollision(path);
	collision = new Collision(collider, &desRect, nullptr, &position);
}

void Object::move() {
	if (!check_death && !check_pause) {

	}
}

void Object::setProperties() {
	File::getProperties(type, stat);
	texture = TextureManagement::LoadTexture(stat.source, renderer);
	position.x = 0;
	position.y = 6 * TILE_HEIGHT;
}

void Object::render() {
	if (status != lastStatus) frameCount = 0;
	if (frameCount == frame[status].maxFrame - 1) frameCount = 0;
	frameCount++;
	srcRect = wareClips[status][frameCount / frame[status].perFrame];
	lastStatus = status;
	SDL_RenderCopyEx(renderer, texture, &srcRect, &desRect, NULL, NULL, flip);
}

void Object::setLocation() {
	/*while (collider[map_y][map_x] == 0) {
		map_x = Math::Casuale::casuale(0, w - 1);
		map_y = Math::Casuale::casuale(0, h - 1);
	}*/

	map_x = 0;
	map_y = 6;

	//next_map_x = map_x;
	//next_map_y = map_y;

	desRect = {(((12 - 2) * TILE_WIDTH) + (TILE_WIDTH / 2) + (OBJECT_WIDTH / 2)), ((9 * TILE_HEIGHT) + TILE_HEIGHT - OBJECT_HEIGHT) - 10, OBJECT_WIDTH, OBJECT_HEIGHT };
}



void Object::init() {
	//setCollision(water_town);
	setLocation();
	setProperties();
	setClip();
	setFrameLimit();
	setCollision(water_town);
}

void Object::setFrameLimit() {
	File::getFrameLimit(type, frame);
}
