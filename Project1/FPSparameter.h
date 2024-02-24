#pragma once
#include "label.h"
#include "FPScontroller.h"
class FPSparameter : public Label 
{
public:
	FPSparameter(SDL_Renderer* renderer, int x, int y, int w, int h) : Label(renderer, x, y, w, h) {
		std::cout << "FPS parameter constructor called" << std::endl;
	}

	~FPSparameter() {
		std::cout << "FPS parameter destructor called" << std::endl;
	}
	void updateFPS();

};

