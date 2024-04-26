#pragma once
#include "aniamted_obj.h"
#include "protocol.h"

class damageTile : public Animated
{
protected:
	//std::string type;
	Effect effect;
	int damage;
	Stat stat;
	Protocol* protocol;
	TileState status;
	TileState lastStatus;
public:
	damageTile(SDL_Renderer* renderer, std::string type) : Animated(renderer) {
		code = 99;
		this->type = type;
	}

	~damageTile() {

	}

	virtual void init() override;
	virtual void render() override;
	virtual void handleEvents();
	void setProperties();
	void setProtocol();
	virtual void setTexture() override;

};

