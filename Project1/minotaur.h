#pragma once
#include "computer.h"
class Minotaur : public Computer
{
private:
public:
	static SDL_Texture* vessel;
	Minotaur(SDL_Renderer* renderer, std::string type = "minotaur") : Computer(renderer, type) {
		std::cout << "construc" << std::endl;
	}
	~Minotaur() {

	}
	virtual void draw() override;
};

