#pragma once
#include "aniamted_obj.h"
class Missle : public Animated
{
protected:
	MissleState status = FORMATION;
	double angle = 0;
public:
	static void loadTexture();

	Missle(SDL_Renderer* renderer) : Animated(renderer) {
		desRect.x = 64;
		desRect.y = 64;
	}

	~Missle() {

	}
	void setAngle(double angle);
	virtual void init() override;
	virtual void render() override;
	virtual void draw();
	virtual void handleEffect();
};

