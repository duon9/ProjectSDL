#pragma once

#include "computer.h"
class Skeleton : public Computer
{
public:
	static SDL_Texture* vessel;
	//virtual void draw() override;
	Skeleton(SDL_Renderer* renderer, std::string type = "skeleton") : Computer(renderer, type) {

	}

	~Skeleton() {

	}

};

