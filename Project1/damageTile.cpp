#include "damageTile.h"
#include "global.h"

void damageTile::init() {
	setProtocol();
	setProperties();
	setClip();
	setFrameLimit();
	setTexture();
}

void damageTile::render() {
	frameCount++;
	if (status == FORMATIONS || status == FINAL) {
		if (frameCount < (*frame)[FORMATION].maxFrame) {
			status = FORMATIONS;
			srcRect = (*wareClips)[FORMATION][frameCount / (*frame)[FORMATIONS].perFrame];
		}
		else {
			status = INFINITE;
			if (frameCount >= (*frame)[FORMATIONS].maxFrame + (*frame)[INFINITE].maxFrame) {
				frameCount = (*frame)[FORMATIONS].maxFrame;
			}
			srcRect = (*wareClips)[FINAL][(frameCount - (*frame)[FORMATIONS].maxFrame) / (*frame)[INFINITE].perFrame];
		}
	}
	if (status == ENDING) {
		if (frameCount < (*frame)[ENDING].maxFrame) {
			srcRect = (*wareClips)[ENDING][(frameCount / (*frame)[ENDING].perFrame)];
		}
		else {
			return;
		}
	}
	SDL_RenderCopy(global::renderer, texture, &srcRect, &desRect);
}

void damageTile::handleEvents() {
	listen(global::e);
}

void damageTile::setProperties() {
	if (global::stats[type] == nullptr) {
		global::stats[type] = new Stat();
		File::getProperties(type, global::stats[type]);
		stat = *global::stats[type];
	}
	else {
		stat = *global::stats[type];
	}
	setSize(stat.width, stat.height);
}

void damageTile::setProtocol() {
	protocol = new Protocol(code);
}

void damageTile::setTexture() {
	if (global::resources[type] == nullptr) {
		global::resources[type] = TextureManagement::LoadTexture(stat.source, global::renderer);
		texture = global::resources[type];
	}
	else {
		texture = global::resources[type];
	}
}

void damageTile::listen(SDL_Event e) {
	if (!check_death) {
		SDL_Rect interact;
		int dame;
		if (protocol->listen(&e, interact, dame)) {
			SDL_Rect rec = getRect();
			if (SDL_HasIntersection(&interact, &rec)) {
				stat.health -= dame;
			}
		}
	}
}

void damageTile::handleLogic() {
	if (!check_death) {
		if (stat.health <= 0) {
			status = ENDING;
			frameCount = 0;
			check_death = true;
		}
	}
}

void damageTile::handleMissle(int damage, Effect effect) {
	stat.health -= damage;
}