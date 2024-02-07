#pragma once
#include "interact_obj.h"
#include "constant.h"
#include <queue>
#include "utils.h"

class Player : public Object
{
private:
	std::string source;

public:

	Player(SDL_Renderer* renderer, std::string source) : Object(renderer) {
		this->renderer = renderer;
		this->source = source;
		std::cout << "Player constructor initialize" << std::endl;
	}
	~Player() {
		/**
		*Destructor
		*/
	}

	virtual void init() override;
	virtual void render() override;
	virtual void setClip() override;
	//virtual void setSkill() override;
	void handleUserEvents(SDL_Event e);
};

