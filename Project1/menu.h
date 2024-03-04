#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>
#include <string>
#include <iostream>
#include "button.h"
#include "animated_button.h"
//#include "zMath.h"
//#include "zDraw.h"
//#include "zGame.h"



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
	//Button* newGame = nullptr;
	//Button* loadGame = nullptr;
	AnimatedButton* btn = nullptr;
	//std::vector<Button> menuButton;
	TTF_Font* menuFont = nullptr;
	TTF_Font* btnFont = nullptr;
	SDL_Renderer* renderer = nullptr;
	//SDL_Surface* menuSurface = nullptr;
	//SDL_Texture* menuTexture = nullptr;
	Uint64 now, last;
	double deltaTime;
	int cubesLength;
	Cube cubes[1000];
};
