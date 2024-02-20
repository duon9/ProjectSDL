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
	virtual void setProperties();
	virtual void setFrameLimit();
	bool collisionHandle(std::vector<std::vector<int>> collider);
	void colliderLoad(std::string path);
	virtual void move();
	int change();
	virtual void setLocation();
	virtual void init() override;
	virtual void render() override;
protected:
	int w, h;
	std::vector<std::vector<int>> collider;
	std::vector<Frame> frame;
	Stat stat;
	std::string type;
	std::vector<Skill> skillSet;
	std::vector<std::vector<SDL_Rect>> wareClips;

	SDL_RendererFlip flip = SDL_FLIP_NONE;

	int frameCount;
	int frameTick;
	Orient* orient = new Orient();
	charState lastStatus = IDLE;
	charState status = charState::IDLE;
	charState next_status = charState::IDLE; // still use, do not delete
	int next_map_x, next_map_y;

	int velo_x;
	int velo_y;

	bool check_run = false;
	bool check_pause = false;
	bool check_attack = false;
	bool check_death = false;
	bool check_take_damage = false;
	bool isAction = false;
};