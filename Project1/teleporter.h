#pragma once
#include "entity.h"

class Teleporter : public Entity
{
private:

public:
	Teleporter(SDL_Renderer* renderer) : Entity(renderer) {

	}
	
	~Teleporter() {

	}
	virtual void init() override;
	void teleport();


};

