#pragma once
#include "Missle.h"

class HolySpear : public Missle
{
private:
	static std::vector<std::vector<SDL_Rect>> clips;
	static std::vector<Frame> limits;
	static SDL_Texture* vessel;
	const static int damage = 10000;
public:
	HolySpear(SDL_Renderer* renderer, SDL_Point currPos, SDL_Point desPos, SDL_Point camera, Uint32 code) : Missle(renderer, currPos, desPos, camera, code) {
		wareClips = HolySpear::clips;
		frame = HolySpear::limits;
		speed = 15;
	}

	~HolySpear() {

	}
	static void loadClips();
	static void loadTexture(SDL_Renderer* renderer);
	virtual void draw() override;
};

