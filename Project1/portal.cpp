#include "portal.h"
#include "global.h"

SDL_Texture* Portal::vessel = nullptr;
std::vector<SDL_Rect> Portal::clips;

void Portal::loadTexture() {
	
	vessel = TextureManagement::LoadTexture("assets/characters/portal.png", global::renderer);
}

void Portal::render() {
	if (frameCount >= 100) frameCount = 0;
	SDL_RenderCopyEx(renderer, vessel, &clips[frameCount / 5], &desRect, NULL, NULL, SDL_FLIP_NONE);
	frameCount++;
}

void Portal::loadClip() {
	clips.push_back({ 0,0,96,80 });
	clips.push_back({ 1* 96,0,96,80 });
	clips.push_back({ 2 * 96,0,96,80 });
	clips.push_back({ 3 * 96,0,96,80 });

	clips.push_back({ 0,1 * 80,96,80 });
	clips.push_back({ 1 * 96,1 * 80,96,80 });
	clips.push_back({ 2 * 96,1 * 80,96,80 });
	clips.push_back({ 3 * 96,1 * 80,96,80 });

	clips.push_back({ 0,2 * 80,96,80 });
	clips.push_back({ 1 * 96,2 * 80,96,80 });
	clips.push_back({ 2 * 96,2 * 80,96,80 });
	clips.push_back({ 3 * 96,2 * 80,96,80 });

	clips.push_back({ 0,3 * 80,96,80 });
	clips.push_back({ 1 * 96,3 * 80,96,80 });
	clips.push_back({ 2 * 96,3 * 80,96,80 });
	clips.push_back({ 3 * 96,3 * 80,96,80 });

	clips.push_back({ 0,4 * 80,96,80 });
	clips.push_back({ 1 * 96,4 * 80,96,80 });
	clips.push_back({ 2 * 96,4 * 80,96,80 });
	clips.push_back({ 3 * 96,4 * 80,96,80 });
}

void Portal::init() {
	desRect.w = 100;
	desRect.h = 100;
	code = 99;
}