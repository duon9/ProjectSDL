#pragma once
#include "label.h"
class Bar : public Label
{
protected:
	SDL_Rect outlineRect; 
	SDL_Rect healthRect;  
	SDL_Color color;

	int maxWidth;  
	int currentProperty;  
	int maxProperty;  

public:
	Bar(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Color color) : Label(renderer, x, y, w, h) {
		outlineRect = { x, y, w, h};
		healthRect = { x + 1, y + 1, w - 2, h - 2 };
		maxWidth = w;
		std::cout << "Bar constructor called" << std::endl;
		this->color = color;
	}

	~Bar() {
		std::cout << "Bar destructor called" << std::endl;
	}

	//virtual void init() override;
	virtual void render() override;
	void setProperties(int maxHealth);
	void updateProperties(int newHealth);
	void updateBar();
};

