#pragma once
#include "Missle.h"

class LightingEagle : public Missle
{
private:
	static std::vector<std::vector<SDL_Rect>> clips;
	static std::vector<Frame> limits;
	static SDL_Texture* vessel;
	const static int damage = 1000;

public:
	LightingEagle(SDL_Renderer* renderer, SDL_Point currPos, SDL_Point desPos, SDL_Point camera, Uint32 code) : Missle(renderer, currPos, desPos, camera, code) {
		wareClips = &LightingEagle::clips;
		frame = &LightingEagle::limits;
		speed = 5;
	}

	~LightingEagle() {

	}
	static void loadClips();
	static void loadTexture(SDL_Renderer* renderer);
	//void fade();
	virtual void draw() override;
	//virtual void projectile() override;
	//virtual void handleEffect(SDL_Rect target) override;
	//void push();
};

