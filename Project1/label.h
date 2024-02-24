#pragma once
#include "entity.h"

class Label : public Entity
{
private:
protected:
	SDL_Color textColor;
	TTF_Font* font = nullptr;
	std::string text;

public:
	Label(SDL_Renderer* renderer, int x, int y, int w, int h) : Entity(renderer) {
		std::cout << "Label constructor called" << std::endl;
		this->desRect = { x, y, w, h };
	}

	~Label() {
		std::cout << "Label destructor called" << std::endl;
		TTF_CloseFont(font);
	}

	virtual void init() override;
	virtual void render() override;
};

