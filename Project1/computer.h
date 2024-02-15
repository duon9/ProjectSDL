#pragma once

#include "interact_obj.h"
#include "utils.h"

enum RandomOrient {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Computer : public Object
{
private:
	bool find_enemy = false;

public:
	Computer(SDL_Renderer* renderer, std::string type) : Object(renderer) {
		std::cout << "Computer class constructor called \n";
		this->renderer = renderer;
		this->type = type;
	}

	~Computer() {
		std::cout << "Computer class destructor called \n";
	}

	//virtual void setClip() override;
	//virtual void init() override;
	//virtual void render() override;
	void randomBotMovement();
};
