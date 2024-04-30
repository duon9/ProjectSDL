#pragma once
#include "damageTile.h"

class Wave : public damageTile
{
private:

public:
	Wave(SDL_Renderer* renderer) : damageTile(renderer, "wave") {
		init();
		//create();
	}

	~Wave() {

	}
};

