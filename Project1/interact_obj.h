#pragma once
#include "entity.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "utils.h"
#include <iostream>
#include "constant.h"
#include <vector>
#include "skill.h"

class Interact_Object : public Entity {
public:
	short getHealth();
	short getMana();
	short getLevel();
	short getExp();
	short getSpeed();
	short getMagicDamage();
	short getRange();
	short getAmmor();
	short getMagicResistance();
	short getPhysicDamage();
	short getCrit();

	void updateHealth(short newHealth);
	void updateMana(short newMana);
	void updateLevel(short newLevel);
	void updateExp(short newExp);
	void updateSpeed(short newSpeed);
	void updateMagicDamage(short newMagicDamage);
	void updateRange(short newRange);
	void updateAmmor(short newAmmor);
	void updateMagicResistance(short newMagicResistance);
	void updatePhysicDamage(short newPhysicDamage);
	void updateCrit(short newCrit);

	void collisionProcess(); // still planning
	void usingSkill(); // still planning

protected:
	short health, mana, level, exp, speed, magicDamage, range, armor, magicResistance, physicDamage, crit;
	State currState;
	charState currCharState;
	std::vector<Skill> skillSet;
};