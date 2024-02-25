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
	//position.x = 0;
	//position.y = 6 * TILE_HEIGHT;
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
	

	/*position.x = Math::Casuale::casuale(0, 1000);
	position.y = Math::Casuale::casuale(0, 1000);*/

	position.x = 10 * 32;
	position.y = 6 * 32;

	desRect = { 0,0, OBJECT_WIDTH, OBJECT_HEIGHT };
	
}

void Object::updateObjectScreenPosition(SDL_Rect *camera) {
	desRect.x = position.x - camera->x;
	desRect.y = position.y - camera->y;
}

void Object::init() {
	setProtocolCode();
	setProtocol();
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

SDL_Point Object::getPosition() {
	return position;
}

void Object::listen(SDL_Event *e) {
	SDL_Rect* interact = nullptr;
	int* damage = nullptr;
	protocol->listen(e, interact, damage);
	if (interact == nullptr || damage == nullptr) {
		//std::cout << "null" << std::endl;
		return;
	}
	else {
		if (collision->rectColliding(getRect(), *interact)) {
			stat.health -= *damage;
		}
	}
	delete interact;
	delete damage;
}

void Object::attack() {
	SDL_Rect attack = getRect();
	if (flip = SDL_FLIP_NONE) {
		attack.x += attack.w;
		attack.w += stat.range * TILE_WIDTH;
	}
	else {
		attack.x -= attack.w;
		attack.w += stat.range * TILE_WIDTH;
	}
	std::cout << "send successed" << std::endl;
	std::cout << attack.x << " " << attack.y << " " << attack.w << " " << attack.h << std::endl;
	protocol->send(&attack, &stat.damage);
}