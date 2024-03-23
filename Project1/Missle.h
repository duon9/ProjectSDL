#pragma once
#include "aniamted_obj.h"
#include "math.h"
class Missle : public Animated
{
protected:
	MissleState status = FORMATION;
	double angle = 0;
	bool isCollide = false;
	Uint32 code;
	int speed = 5;
	Math::Vector v;
public:
	

	Missle(SDL_Renderer* renderer, SDL_Point currPos, SDL_Point desPos, Uint32 code) : Animated(renderer) {
		desRect.x = 64;
		desRect.y = 64;
		this->code = code;
		this->v = Math::Vector(currPos, desPos);
		desRect.x = currPos.x;
		desRect.y = currPos.y;
		this->v.normalize();
	}

	~Missle() {

	}
	void setAngle(double angle);
	virtual void init() override;
	virtual void render() override;
	virtual void draw();
	virtual void handleEffect();
};

