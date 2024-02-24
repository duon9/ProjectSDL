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
	map_x = 1;
	map_y = 20;

	position.x = map_x * TILE_WIDTH;
	position.y = map_y * TILE_HEIGHT;
	desRect = { 0,0, OBJECT_WIDTH, OBJECT_HEIGHT };
	
}

void Object::updateObjectScreenPosition(SDL_Rect *camera) {
	desRect.x = position.x - camera->x;
	desRect.y = position.y - camera->y;
}



void Object::init() {
	setLocation();
	setProperties();
	setClip();
	setFrameLimit();
	setCollision(water_town);
}

void Object::setFrameLimit() {
	File::getFrameLimit(type, frame);
}

SDL_Rect Object::getRect() {
	return { position.x, position.y, desRect.w, desRect.h };
}