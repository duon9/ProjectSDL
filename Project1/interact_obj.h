#pragma once
#include "entity.h"
#include "utils.h"
#include <iostream>
#include "constant.h"
#include "skill.h"
#include "math.h"
#include <cmath>
#include "collision.h"
#include "aniamted_obj.h"

class Object : public Animated {
public:

	Object(SDL_Renderer* renderer) : Animated(renderer) {
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
	void listen(SDL_Event* e);
	void attack();

	virtual void logicHandle();
	virtual void setProperties();
	virtual void setCollision();
	virtual void move();
	virtual void setLocation() override;
	virtual void init() override;
	virtual void render() override;
	bool check_death = false;
	void resurrect(int time);
	static std::vector<std::vector<int>> collider;
protected:
	//std::vector<std::vector<int>> collider;
	Stat stat;
	std::vector<Skill> skillSet;
	Collision* collision;
	int timer = 0;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	charState lastStatus = IDLE;
	charState status = IDLE;
	//charState next_status = IDLE; // still use, do not delete
	int velo_x;
	int velo_y;
	bool check_pause = false;
	bool check_attack = false;
	bool check_take_damage = false;
};