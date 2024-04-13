#pragma once
#include "Missle.h"

class WaterBall : public Missle
{
private:
	static std::vector<std::vector<SDL_Rect>> clips;
	static std::vector<Frame> limits;
	static SDL_Texture* vessel;
public:
	WaterBall(SDL_Renderer* renderer, SDL_Point currPos, SDL_Point desPos, SDL_Point camera, Uint32 code) : Missle(renderer, currPos, desPos, camera, code) {
		wareClips = &WaterBall::clips;
		frame = &WaterBall::limits;
		damage = 100000;
	}

	~WaterBall() {

	}
	static void loadClips();
	static void loadTexture(SDL_Renderer* renderer);
	virtual void draw() override;
};

