#pragma once
#include "interact_obj.h"
#include "constant.h"
#include "utils.h"
#include "interface.h"
#include "sfx.h"

class Player : public Object
{
protected:
	Interface* interface = nullptr;
	SFX* attackSound = new SFX();
	SFX* runSound = new SFX();
	Orient orient;
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
	void handleBarDisplay();
	bool isInvisible = false;
	void setBarProperties();
	void setSFX();
	virtual void init() override;
	virtual void move() override;
	virtual void handleUserEvents(SDL_Event *e);
	virtual void setLocation() override;
	virtual void setCollision() override;
	virtual void setProtocolCode() override;
	/*bool collisionHandle(std::vector<std::vector<int>> collider);*/
};
