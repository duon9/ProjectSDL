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
	void collisionHandle();
	virtual void setCollision(std::string path);
	virtual void move();
	virtual void setLocation();
	virtual void init() override;
	virtual void render() override;
	bool check_death = false;
	void resurrect(int time);
protected:
	std::vector<std::vector<int>> collider;
	Stat stat;
	std::vector<Skill> skillSet;
	Collision* collision;
	int timer = 0;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	charState lastStatus = IDLE;
	charState status = IDLE;
	charState next_status = IDLE; // still use, do not delete
	int velo_x;
	int velo_y;
	bool check_run = false;
	bool check_pause = false;
	bool check_attack = false;
	bool check_take_damage = false;
};