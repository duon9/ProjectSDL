#pragma once
#include "interact_obj.h"
#include "constant.h"
#include "utils.h"
#include "interface.h"
#include "sfx.h"
#include "WaterBall.h"
#include "FireBall.h"
#include "IceLancet.h"
#include "HolySpear.h"
#include "FireBomb.h"
#include "global.h"
#include "LBitmapFont.h"
#include "LightingEagle.h"
#include "HealCloud.h"

#define MAX_TYPE 8

class Player : public Object
{
private:
	//static SDL_Texture* vessel;
	SDL_Rect* lumi = nullptr;
protected:
	Interface* interface = nullptr;
	SFX* attackSound = new SFX();
	SFX* runSound = new SFX();
	Orient orient;
	int magic = 1;
	//LBitmapFont llma;
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
	Stat& getStat();
	SDL_Point& getAddressLocation();
	void handleBarDisplay();
	bool isInvisible = false;
	void setBarProperties();
	void setSFX();
	void reload();
	SDL_Point getExactPosition();
	virtual void init() override;
	virtual void move() override;
	virtual void handleUserEvents(SDL_Event *e);
	virtual void setLocation() override;
	void setLocation(SDL_Point p);
	virtual void setCollision() override;
	virtual void setProtocolCode() override;
	//virtual void draw() override;
	virtual void setAbility() override;
	virtual void setLumination() override;
	SDL_Point getCursorPosition(SDL_Event* e);
};
