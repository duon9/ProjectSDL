#pragma once
#include "aniamted_obj.h"

class Ray : public Animated
{
public:
	Ray(SDL_Renderer* renderer, SDL_Point currPos, SDL_Point desPos, SDL_Point camera, Uint32 code) : Animated(renderer) {

	}

	~Ray() {

	}
};

