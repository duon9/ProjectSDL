#pragma once
#include "Missle.h"

#define DAMAGE 100

class WaterBall : public Missle
{
private:
	static std::vector<std::vector<SDL_Rect>> wareClips;
	static SDL_Texture* vessel;
	const static int damage = DAMAGE;
public:
	static void load();
};

