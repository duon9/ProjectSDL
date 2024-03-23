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
	WaterBall(SDL_Renderer* renderer, SDL_Point currPos, SDL_Point desPos, Uint32 code) : Missle(renderer, currPos, desPos, code) {

	}

	~WaterBall() {

	}
	static void loadClips();
	static void loadTexture(SDL_Renderer* renderer);
};

