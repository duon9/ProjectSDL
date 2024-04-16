#pragma once
#include "computer.h"
#define START_EXPLOSION 130 
#define END_EXPLOSION 180

class NightBorne : public Computer
{
private:
	int timer = 0;
public:
	NightBorne(SDL_Renderer* renderer, std::string type = "night") : Computer(renderer, type) {

	}

	~NightBorne() {

	}
	static SDL_Texture* vessel;
	//virtual void draw() override;
	virtual void death() override;
};

