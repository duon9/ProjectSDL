#pragma once

#include "interact_obj.h"
#include "utils.h"
#include "player.h"
#include <vector>
#include "math.h"

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

	//void randomBotMovement();
	bool moveTo(SDL_Point target);
	bool isReachDestination(Math::Vector v);
	Player* trackNearestTarget(std::vector<Player*>& target);
	void chaseTarget(std::vector<Player*>& targets);
	virtual void setProtocolCode() override;
};
