#pragma once
#include "interact_obj.h"
#include "constant.h"
#include "utils.h"
#include "interface.h"
#include "sfx.h"
#include "WaterBall.h"
#include "global.h"

class Player : public Object
{
private:
	//static SDL_Texture* vessel;
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

	static SDL_Texture* vessel;

	void handleBarDisplay();
	bool isInvisible = false;
	void setBarProperties();
	void setSFX();
	void reload();
	virtual void init() override;
	virtual void move() override;
	virtual void handleUserEvents(SDL_Event *e);
	virtual void setLocation() override;
	void setLocation(int x, int y);
	virtual void setCollision() override;
	virtual void setProtocolCode() override;
	virtual void draw() override;
	virtual void setAbility() override;
	SDL_Point getCursorPosition(SDL_Event* e);
};
