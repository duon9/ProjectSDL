#pragma once
#include "computer.h"
class NightBorne : public Computer
{
public:
	NightBorne(SDL_Renderer* renderer, std::string type = "night") : Computer(renderer, type) {

	}

	~NightBorne() {

	}
	static SDL_Texture* vessel;
	virtual void draw() override;
	virtual void death() override;
};

