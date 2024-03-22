#include "bullet.h"

void Bullet::render() {
	if (isCollide) return;
	SDL_SetRenderDrawColor(renderer, R, G, B, A);
	SDL_RenderFillRect(renderer, &rect);
}

void Bullet::handleProjectile() {
	rect.x += v.getX() * speed;
	rect.y += v.getY() * speed;
}

//bool Bullet::handleCollision(Entity* target) {
//	if (isCollide) return false;
//	if (target->getProtocolCode() == code) {
//		return false;
//	}
//	else {
//		target->handleMissle(damage);
//		return true;
//	}
//}

void Bullet::terminate() {
	isCollide = true;
}