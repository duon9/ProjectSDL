#include "Missle.h"


void Missle::render() {

}

void Missle::init() {

}

void Missle::handleEffect() {

}

void Missle::draw() {
	SDL_RenderCopyEx(renderer, NULL, &srcRect, &desRect, angle, NULL, SDL_FLIP_NONE);
}

void Missle::setAngle(double angle) {
	this->angle = angle;
}