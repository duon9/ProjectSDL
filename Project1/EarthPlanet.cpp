#include "EarthPlanet.h"
#define SIZE 500
void EarthPlanet::loadClips() {
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			clips.push_back({ j * SIZE, i * SIZE, SIZE, SIZE });
		}
		luff.push_back(clips);
		clips.clear();
	}
}

void EarthPlanet::loadTexture() {
	texture1 = TextureManagement::LoadTexture("assets/menu/g1.png", renderer);
	texture2 = TextureManagement::LoadTexture("assets/menu/g2.png", renderer);
	texture3 = TextureManagement::LoadTexture("assets/menu/g3.png", renderer);
	texture4 = TextureManagement::LoadTexture("assets/menu/g4.png", renderer);
}

void EarthPlanet::init() {
	loadClips();
	loadTexture();
	desRect.w = 500;
	desRect.h = 500;
	desRect.x = SCREEN_WIDTH / 2 - desRect.w / 2;
	desRect.y = SCREEN_HEIGHT / 2 - desRect.h / 2;
}

void EarthPlanet::render() {
	int r = frameCount / COUNT;
	int c = frameCount % COUNT;
	if (c < HALFCOUNT && r < HALFCOUNT) {
		srcRect = luff[r][c];
		SDL_RenderCopy(renderer, texture1, &srcRect, &desRect);
	}
	else if (c >= HALFCOUNT && r < HALFCOUNT) {
		srcRect = luff[r][c - HALFCOUNT];
		SDL_RenderCopy(renderer, texture2, &srcRect, &desRect);
	}
	else if (c < HALFCOUNT && r >= HALFCOUNT) {
		srcRect = luff[r - HALFCOUNT][c];
		SDL_RenderCopy(renderer, texture3, &srcRect, &desRect);
	}
	else if (r >= HALFCOUNT && c >= HALFCOUNT) {
		srcRect = luff[r-HALFCOUNT][c-HALFCOUNT];
		SDL_RenderCopy(renderer, texture4, &srcRect, &desRect);
	}

	frameCount++;
	if (frameCount == MAX_FRAME) frameCount = 0;
}