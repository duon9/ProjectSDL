#pragma once
#include "interact_obj.h"
#include "constant.h"
#include "utils.h"

class Player : public Object
{
private:

public:

	Player(SDL_Renderer* renderer, std::string type) : Object(renderer) {
		this->renderer = renderer;
		this->type = type;
		std::cout << "Player constructor initialize" << std::endl;
	}
	~Player() {
		/**
		*Destructor
		*/
	}

	//virtual void init() override;
	void handleUserEvents(SDL_Event e);
	/*bool collisionHandle(std::vector<std::vector<int>> collider);*/
};
