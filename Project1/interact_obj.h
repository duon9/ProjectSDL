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
#include "global.h"
#include "TimerManager.h"

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
	virtual void listen(SDL_Event* e);
	void attack();
	void setRandomId();
	virtual void handleLogic() override;
	virtual void setAbility();
	virtual void logicHandle();
	virtual void setProperties();
	virtual void setCollision();
	virtual void move();
	virtual void init() override;
	virtual void render() override;
	virtual void draw();
	virtual void death();
	virtual void afterDeath();
	virtual void handleMissle(int damage, Effect effect = NONE) override;
	void handleMissleEffect();
	virtual void setTexture() override;
	void resurrect(int time);
	static std::vector<std::vector<int>> collider;
protected:
	Stat stat;
	Effect effect;
	int id;
	int lastHealth;
	std::vector<Skill> skillSet;
	Collision* collision;
	int timer = 0;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	charState lastStatus = IDLE;
	charState status = IDLE;

	int velo_x;
	int velo_y;
	bool check_pause = false;
	bool check_attack = false;
	bool check_take_damage = false;
};