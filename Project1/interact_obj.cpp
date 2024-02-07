#include "interact_obj.h"


int Object::getAmmor() {
	return armor;
}

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

int Object::getMagicDamage() {
	return magicDamage;
}

int Object::getRange() {
	return range;
}

int Object::getMagicResistance() {
	return magicResistance;
}

int Object::getPhysicDamage() {
	return physicDamage;
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

void Object::updateMagicDamage(int newMagicDamage) {
	magicDamage = newMagicDamage;
}

void Object::updateRange(int newRange) {
	range = newRange;
}

void Object::updateArmor(int newArmor) {
	armor = newArmor;
}

void Object::updateMagicResistance(int newMagicResistance) {
	magicResistance = newMagicResistance;
}

void Object::updatePhysicDamage(int newPhysicDamage) {
	physicDamage = newPhysicDamage;
}

void Object::setClip() {
	std::cout << "a" << std::endl;
}