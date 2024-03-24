#include "interact_obj.h"

std::vector<std::vector<int>> Object::collider;


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

void Object::logicHandle() {
	if (stat.health <= 0) {
		check_death = true;
		status = charState::DEATH;
	}
}

void Object::setCollision() {
	//collider = File::readCollision(path);
	collision = new Collision(Object::collider, &desRect, nullptr, &position);
}

void Object::move() {
	if (!check_death && !check_pause) {

	}
}

void Object::setProperties() {
	File::getProperties(type, stat);
	setSize(stat.width, stat.height);
}

void Object::render() {

	if (status != lastStatus) frameCount = 0;
	if (frameCount == frame[status].maxFrame - 1 && status == DEATH) {
		afterDeath();
		frameCount -= 1;
	}
	else if (frameCount == frame[status].maxFrame - 1) {
		frameCount = 0;
	}
	frameCount++;
	srcRect = wareClips[status][frameCount / frame[status].perFrame];
	lastStatus = status;
	//SDL_RenderCopyEx(renderer, texture, &srcRect, &desRect, NULL, NULL, flip);
	/*SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &desRect);*/

	draw();
}

void Object::setLocation() {
	

	position.x = Math::Casuale::casuale(0, 500);
	position.y = Math::Casuale::casuale(0, 500);
	/*position.y = Math::Casuale::casuale(0, 1000);*/

	//desRect = { 0,0, 54, 54};
	
}

void Object::init() {
	setProtocolCode();
	setProtocol();
	setLocation();
	setProperties();
	setClip();
	setFrameLimit();
	setCollision();
}

void Object::listen(SDL_Event *e) {
	if (!check_death && !check_pause) {
		SDL_Rect interact;
		int dame;
		if (protocol->listen(e, interact, dame)) {
			SDL_Rect rec = getRect();
			if (SDL_HasIntersection(&interact, &rec)) {
				stat.health -= dame;
				/*status = TAKEDAMAGE;
				if (stat.health <= 0) {
					check_death = true;
					status = DEATH;
				}*/
			}
		}
	}
}

void Object::attack() {
	SDL_Rect attack = getRect();
	if (flip == SDL_FLIP_NONE) {
		attack.x += (attack.w / 2);
		attack.w = (stat.range * TILE_WIDTH);
	}
	else if (flip == SDL_FLIP_HORIZONTAL) {
		attack.x += (attack.w / 2 - (stat.range * TILE_WIDTH));
		attack.w = (stat.range * TILE_WIDTH);
	}

	
	protocol->send(&attack, &stat.damage);
	frameTick = frame[status].maxFrame - 1;
}

void Object::resurrect(int time) {
	if (status == DEATH) timer++;
	if (timer == time) {
		//std::cout << "Resurrect successed" << std::endl;
		check_death = false;
		status = IDLE;
		setProperties();
		frameCount = 0;
		timer = 0;
	}
}

void Object::draw() {
	SDL_RenderCopyEx(renderer, texture, &srcRect, &desRect, NULL, NULL, flip);
}

void Object::death() {
	return;
}

void Object::afterDeath() {
	return;
}

void Object::setAbility() {
	return;
}

void Object::handleMissle(int damage) {
	stat.health -= damage;
	/*status = TAKEDAMAGE;
	if (stat.health <= 0) {
		check_death = true;
		status = DEATH;
	}*/
}

void Object::handleLogic() {
	if (stat.health < 0) {
		status = DEATH;
		check_death = true;
	}
	else if (stat.health < lastHealth) {
		status = TAKEDAMAGE;
	}
	lastHealth = stat.health;
}