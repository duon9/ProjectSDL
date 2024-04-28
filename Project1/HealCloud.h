#pragma once

#include "damageTile.h"


class HealCloud : public damageTile
{
private:
	SDL_Rect* lumi;

public:
	HealCloud(SDL_Renderer* renderer) : damageTile(renderer, "healTile") {
		code = 30;
		init();
		//setLumination();
	}

	~HealCloud() {

	}
	virtual void setLumination() override;
	virtual void handleEvents() override;
	virtual void handleLogic() override;
	void incinerate();
	SDL_Rect* getDamageRect();
};

