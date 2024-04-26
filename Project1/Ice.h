#pragma once
#include "damageTile.h"

class Ice : public damageTile
{
private:

public:
	Ice(SDL_Renderer* renderer) : damageTile(renderer, "iceTile") {
		init();
		create();
	}

	~Ice() {

	}

	void create();
	void clear();
};

