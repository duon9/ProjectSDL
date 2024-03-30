#pragma once
#include "computer.h"
#include "FireBomb.h"

class FireWorm : public Computer
{
private:
	int timer = 0;
public:
	FireWorm(SDL_Renderer* renderer, std::string type = "fireworm") : Computer(renderer, type) {

	}

	~FireWorm() {

	}
	static SDL_Texture* vessel;
	virtual void draw() override;
	virtual void chaseTarget(Player* target) override;
};

