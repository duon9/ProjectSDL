#pragma once
#include "damageTile.h"

class Fire : public damageTile
{
private:
	SDL_Rect* lumi;

public:
	Fire(SDL_Renderer* renderer) : damageTile(renderer, "fireTile") {
		code = 30;
		init();
		//setLumination();
	}

	~Fire() {

	}
	virtual void setLumination() override;
	virtual void handleEvents() override;
	virtual void handleLogic() override;
	void incinerate();
	SDL_Rect* getDamageRect();
};

