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
	if (health < 0) {
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