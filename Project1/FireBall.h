#pragma once
#include "Missle.h"

class FireBall : public Missle
{
private:
	static std::vector<std::vector<SDL_Rect>> clips;
	static std::vector<Frame> limits;
	static SDL_Texture* vessel;
	//const static int damage = 1000;
	SDL_Rect* lumi = nullptr;
	
public:
	FireBall(SDL_Renderer* renderer, SDL_Point currPos, SDL_Point desPos, SDL_Point camera, Uint32 code) : Missle(renderer, currPos, desPos, camera, code) {
		wareClips = &FireBall::clips;
		frame = &FireBall::limits;
		speed = 5;
		damage = 100000000;
		lumi = new SDL_Rect();
		lumi->w = 360;
		lumi->h = 360;
		lumi->x = desRect.x + desRect.w / 2 - lumi->w / 2;
		lumi->y = desRect.y + desRect.h / 2 - lumi->h / 2;
		effect = HPDrain;
		push();
	}

	~FireBall() {

	}
	static void loadClips();
	static void loadTexture(SDL_Renderer* renderer);
	void fade();
	virtual void draw() override;
	virtual void projectile() override;
	virtual void handleEffect(SDL_Rect target) override;
	void push();
};

