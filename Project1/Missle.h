#pragma once
#include "aniamted_obj.h"
#include "math.h"
#include "constant.h"
class Missle : public Animated
{
protected:
	MissleState state = FORMATION;
	double angle = 0;
	bool isCollide = false;
	Uint32 code;
	int speed = 5;
	Math::Vector v;
public:
	

	Missle(SDL_Renderer* renderer, SDL_Point currPos, SDL_Point desPos, SDL_Point camera, Uint32 code) : Animated(renderer) {
		desRect.w = MISSLE_WIDTH;
		desRect.h = MISSLE_HEIGHT;
		this->code = code;
		this->v = Math::Vector(currPos, desPos);
		desRect.x = currPos.x;
		desRect.y = currPos.y;
		position.x = camera.x + currPos.x;
		position.y = camera.y + currPos.y;
		this->angle = v.countAngle();
		this->v.normalize();
	}

	~Missle() {

	}
	void setAngle(double angle);
	virtual void init() override;
	virtual void render() override;
	virtual void draw();
	virtual void handleEffect(SDL_Rect target);
	virtual bool isCollision(SDL_Rect target);
	void projectile();
};

