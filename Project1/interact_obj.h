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

class Object : public Entity {
public:

	Object(SDL_Renderer* renderer) : Entity(renderer) {
		std::cout << "Object constructor initialize \n";
	}
	~Object() {
		// destructor

		std::cout << "Object class destructor called" << std::endl;
	}

	int getHealth();
	int getMana();
	int getLevel();
	int getExp();
	int getSpeed();
	int getMagicDamage();
	int getRange();
	int getAmmor();
	int getMagicResistance();
	int getPhysicDamage();

	void updateHealth(int newHealth);
	void updateMana(int newMana);
	void updateLevel(int newLevel);
	void updateExp(int newExp);
	void updateSpeed(int newSpeed);
	void updateMagicDamage(int newMagicDamage);
	void updateRange(int newRange);
	void updateArmor(int newArmor);
	void updateMagicResistance(int newMagicResistance);
	void updatePhysicDamage(int newPhysicDamage);

	//virtual void collisionProcess(); // still planning
	//virtual void spellCast(); // still planning

	//virtual void setSkill();
	virtual void setClip();

protected:
	int health, mana, level, exp, speed, magicDamage, range, armor, magicResistance, physicDamage;
	
	std::vector<Skill> skillSet;

	SDL_Rect idleFrame[10];
	SDL_Rect runFrame[10];
	SDL_Rect attackFrame[10];
	SDL_Rect spellcastFrame[10];
	SDL_Rect deathFrame[10];

	SDL_RendererFlip flip = SDL_FLIP_NONE;
	SDL_Texture* texture = nullptr;

	SDL_Rect srcRect;
	SDL_Rect desRect;

	int frameCount = 0;
	int frameTick;
	int frameMove;
	charState lastFrame = charState::IDLE, newFrame = charState::IDLE;

	Orient* orient = new Orient();

	charState status = charState::IDLE;

	int x, y;

	int map_x, map_y;

	bool check_attack = false;
	bool check_death = false;
	bool check_take_damage = false;

};