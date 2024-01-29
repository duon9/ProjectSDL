#pragma once

#include "utils.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include "constant.h"
#include <chrono>
#include <vector>
#include "interface.h"

class Test
{
public:
	Test();
	~Test();
	void init();
	void render();
	void handleEvents();
	void gameLoop();
	void run();
	void renChar();
	void renBack();
	void initChar();
	void baseAttack();
	void runEast();

private:
	Interface* interface = nullptr;
	Orient orient = Orient::EAST;
	charState objectState = charState::STANDING;
	int frameCount = 0;
	int speed = 300;
	std::vector<std::vector<int>> map;
	SDL_Texture* tex = nullptr;
	SDL_Texture* test = nullptr;
	SDL_Texture* wall = nullptr;
	SDL_Texture* grass = nullptr;
	SDL_Rect src;
	SDL_Rect des;

	SDL_Rect mapSrc;
	SDL_Rect mapDes;

	SDL_Window* win = nullptr;
	SDL_Renderer* ren = nullptr;
	SDL_Rect east_clips[8];
	SDL_Rect west_clips[8];
	SDL_Rect south_clips[8];
	SDL_Rect north_clips[8];

	int w = 1366;
	int h = 768;
};
