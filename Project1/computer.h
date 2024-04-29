#pragma once

#include "interact_obj.h"
#include "utils.h"
#include "player.h"
#include <vector>
#include "math.h"
#include "QuestManager.h"

enum RandomOrient {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Computer : public Object
{
private:

protected:
	QuestManager manager = QuestManager::getInstance();
	int range = 30;
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
	bool isInAttackRange();
	bool trackNearestTarget(Player* target);
	bool moveToBlock(SDL_Point block);
	SDL_Point shortestSmartPath();
	virtual void chaseTarget(Player* target);
	virtual void setProtocolCode() override;
	virtual void gift() override;
	//void waitToRevive();
};
