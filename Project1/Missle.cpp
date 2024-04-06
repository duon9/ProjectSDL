#include "Missle.h"
#include "global.h"


void Missle::render() {
	frameCount++;
	if (state == FORMATION || state == FINAL) {
	    if (frameCount < frame[FORMATION].maxFrame) {
	        state = FORMATION;
	        srcRect = wareClips[FORMATION][frameCount / frame[FORMATION].perFrame];
	    }
	    else {
	        state = FINAL;
	        if (frameCount >= frame[FORMATION].maxFrame + frame[FINAL].maxFrame) {
	            frameCount = frame[FORMATION].maxFrame;
	        }
	        srcRect = wareClips[FINAL][(frameCount - frame[FORMATION].maxFrame) / frame[FINAL].perFrame];
	    }
	}
	if (state == IMPACT) {
	    if (frameCount < frame[IMPACT].maxFrame) {
	        srcRect = wareClips[IMPACT][(frameCount/ frame[IMPACT].perFrame)];
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
	if (global::isPause) return;
	if (state == FINAL /*|| state == FORMATION*/) {
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