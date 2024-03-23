#pragma once
#include "Missle.h"

#define DAMAGE 100

class WaterBall : public Missle
{
private:
	static std::vector<std::vector<SDL_Rect>> clips;
	static SDL_Texture* vessel;
	const static int damage = DAMAGE;
public:
	WaterBall(SDL_Renderer* renderer, SDL_Point currPos, SDL_Point desPos, SDL_Point camera, Uint32 code) : Missle(renderer, currPos, desPos, camera, code) {
		wareClips = WaterBall::clips;
		/*desRect.w = MISSLE_WIDTH;
		desRect.h = MISSLE_HEIGHT;
		this->code = code;
		this->v = Math::Vector(currPos, desPos);
		desRect.x = currPos.x;
		desRect.y = currPos.y;
		this->v.normalize();
		this->angle = v.countAngle();*/
	}

	~WaterBall() {

	}
	static void loadClips();
	static void loadTexture(SDL_Renderer* renderer);
	virtual void draw() override;
};

