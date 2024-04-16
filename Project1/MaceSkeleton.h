#pragma once
#include "computer.h"

class MaceSkeleton : public Computer
{
private:
	int timer = 0;
public:
	MaceSkeleton(SDL_Renderer* renderer, std::string type = "mace") : Computer(renderer, type) {

	}

	~MaceSkeleton() {

	}
	static SDL_Texture* vessel;
	//virtual void draw() override;

};

