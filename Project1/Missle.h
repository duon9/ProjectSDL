#pragma once
#include "aniamted_obj.h"
class Missle : public Animated
{
protected:
	int damage;

public:
	static SDL_Texture* vessel;
	virtual void init() override;
	virtual void render() override;
	virtual void handleEffect();
};

