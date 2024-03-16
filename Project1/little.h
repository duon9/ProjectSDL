#pragma once
#include "computer.h"
class Little : public Computer
{
public:
	Little(SDL_Renderer* renderer, std::string type = "little") : Computer(renderer, type) {

	}

	~Little() {

	}
	static SDL_Texture* vessel;
	virtual void draw() override;
};

