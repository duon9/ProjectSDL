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
	if (status != lastStatus) frameCount = 0;
	if (frameCount == (*frame)[status].maxFrame - 1 && status == DEATH) {
		frameCount -= 1;
	}
	else if (frameCount == (*frame)[status].maxFrame - 1) {
		frameCount = 0;
	}
	frameCount++;
	srcRect = (*wareClips)[status][frameCount / (*frame)[status].perFrame];
	lastStatus = status;
	SDL_RenderCopy(global::renderer, texture, &srcRect, &desRect);
}

void damageTile::handleEvents() {

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