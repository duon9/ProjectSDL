#pragma once
#include "computer.h"

class Wizard : public Computer
{
private:

public:
	Wizard(SDL_Renderer* renderer, std::string type = "wizard") : Computer(renderer, type) {

	}

	~Wizard() {

	}
	virtual void chaseTarget(Player* target) override;
};

