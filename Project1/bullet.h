#pragma once
#include "math.h"
#include "entity.h"

#define R 255
#define G 0
#define B 0
#define A 255

class Bullet
{
private:
	int damage = 3000;
	SDL_Renderer* renderer = nullptr;
	Math::Vector v;
	SDL_Rect rect = {0,0,32,32};
	int speed = 5;
	Uint32 code;
	bool isCollide = false;
public:
	Bullet(SDL_Renderer* renderer, SDL_Point orient, SDL_Point curr, Uint32 code) {
		this->renderer = renderer;
		v = Math::Vector(curr, orient);
		this->code = code;
		rect.x = curr.x;
		rect.y = curr.y;
		v.normalize();
	}

	~Bullet() {

	}

	void render();
	void handleProjectile();
	bool handleCollision(Entity* target);
	void terminate();
};

