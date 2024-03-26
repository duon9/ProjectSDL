#pragma once

#include <vector>
#include <iostream>
#include "button.h"
#include "animated_button.h"
#include "header.h"
#include "tutorial.h"
#include "sfx.h"
#include "EarthPlanet.h"

#ifdef __cplusplus
extern "C"
{
#endif

#include "zMath.h"
#include "zDraw.h"
#include "zGame.h"

#ifdef __cplusplus
}
#endif

class Menu
{
public:
	Menu(SDL_Renderer* renderer);
	~Menu();
	void init();
	void render();
	int handleMenuEvents(SDL_Event& e);
	void background();
	void init3D();
private:
	EarthPlanet* earth = nullptr;
	SFX* music = nullptr;
	bool isOpen = false;
	Tutorial* tutorialwindow = nullptr;
	AnimatedButton* btn = nullptr;
	AnimatedButton* load = nullptr;
	AnimatedButton* tutorial = nullptr;
	AnimatedButton* exit = nullptr;
	Header* header = nullptr;
	//std::vector<Button> menuButton;
	TTF_Font* menuFont = nullptr;
	TTF_Font* btnFont = nullptr;
	TTF_Font* headerFont = nullptr;
	SDL_Renderer* renderer = nullptr;
	Uint64 now, last;
	double deltaTime;
	int cubesLength;
	Cube cubes[1000];
};
