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
		//constructor

		std::cout << "Object constructor called \n";
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
	int getRange();
	int getDamage();

	void updateHealth(int newHealth);
	void updateMana(int newMana);
	void updateLevel(int newLevel);
	void updateExp(int newExp);
	void updateSpeed(int newSpeed);
	void updateRange(int newRange);
	void updateDamage(int newDamage);

	virtual void logicHandle();

	//virtual void collisionProcess(); // still planning
	//virtual void spellCast(); // still planning

	//virtual void setSkill();
	virtual void setClip();
	bool collisionHandle(std::vector<std::vector<int>> collider);
	void colliderLoad(std::string path);
	void move();

	virtual void render() override;
protected:
	int w, h;
	std::vector<std::vector<int>> collider;

	int health, prehealth, mana, level, exp, speed, range, damage;
	std::string type;
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

	int frameCount;
	int frameTick;

	bool direction = true;

	charState lastFrame = charState::IDLE, newFrame = charState::IDLE;

	Orient* orient = new Orient();

	charState status = charState::IDLE;
	charState next_status = charState::IDLE;

	int x, y;

	int map_x, map_y;
	int next_map_x, next_map_y;

	bool check_run = false;
	bool check_pause = false;
	bool check_attack = false;
	bool check_death = false;
	bool check_take_damage = false;
};