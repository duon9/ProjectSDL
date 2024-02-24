#pragma once
#include "interact_obj.h"
#include "constant.h"
#include "utils.h"
#include "interface.h"

class Player : public Object
{
protected:
	Interface* interface;
public:

	Player(SDL_Renderer* renderer, std::string type, Interface * interface) : Object(renderer) {
		this->renderer = renderer;
		this->type = type;
		this->interface = interface;
		std::cout << "Player constructor initialize" << std::endl;
	}
	~Player() {
		/**
		*Destructor
		*/
	}

	//virtual void init() override;
	virtual void move() override;
	virtual void handleUserEvents(SDL_Event *e);
	virtual void setLocation() override;
	virtual void setCollision(std::string path) override;
	/*bool collisionHandle(std::vector<std::vector<int>> collider);*/
};
