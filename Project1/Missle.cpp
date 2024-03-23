#include "Missle.h"


void Missle::render() {
	frameCount++;
	if (state == FORMATION || state == FINAL) {
	    if (frameCount < MAX_FORMATION_FRAME) {
	        state = FORMATION;
	        srcRect = wareClips[FORMATION][frameCount / PER_FORMATION_FRAME];
	    }
	    else {
	        state = FINAL;
	        if (frameCount >= MAX_FORMATION_FRAME + MAX_FINAL_FRAME) {
	            frameCount = MAX_FORMATION_FRAME;
	        }
	        srcRect = wareClips[FINAL][(frameCount - MAX_FORMATION_FRAME) / PER_FINAL_FRAME];
	    }
	}
	if (state == IMPACT) {
	    if (frameCount < MAX_IMPACT_FRAME) {
	        srcRect = wareClips[IMPACT][(frameCount/ PER_IMPACT_FRAME)];
	    }
	    else {
	        return;
	    }
	}

	draw();
}

void Missle::init() {

}

void Missle::handleEffect(SDL_Rect target) {
	if (!isCollide) {
		if (isCollision(target)) {
			state = IMPACT;
			isCollide = true;
			frameCount = 0;
		}
	}
}

void Missle::projectile() {
	if (state == FINAL || state == FORMATION) {
		position.x += v.getX() * speed;
		position.y += v.getY() * speed;
	}
}

void Missle::draw() {
	SDL_RenderCopyEx(renderer, NULL, &srcRect, &desRect, angle, NULL, SDL_FLIP_NONE);
}

void Missle::setAngle(double angle) {
	this->angle = angle;
}

bool Missle::isCollision(SDL_Rect target) {
	SDL_Point center = { position.x + desRect.w / 2, position.y + desRect.h / 2 };
	return SDL_PointInRect(&center, &target);
}

int Missle::getDamage() {
	return damage;
}

bool Missle::getCollideState() {
	return isCollide;
}