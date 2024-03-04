#include "menu.h"
#include "zMath.h"
#include "zDraw.h"
#include "zGame.h"
#include <iostream>

Menu::Menu(SDL_Renderer* renderer) : renderer(renderer) {
	std::cout << "Constructor Menu started" << std::endl;
}

Menu::~Menu() {
	//SDL_FreeSurface(menuSurface);
	//SDL_DestroyTexture(menuTexture);
	TTF_CloseFont(menuFont);
	//delete newGame;
	//delete loadGame;
	std::cout << "Constructor Menu free" << std::endl;
}

void Menu::init() {
	//std::cout << "start Menu initialize" << std::endl;
	menuFont = TTF_OpenFont("assets/fonts/test.ttf", 14);
	btnFont = TTF_OpenFont(font1.c_str(), 20);
	if (menuFont == nullptr) std::cout << "menu font is null " << std::endl;

	//newGame = new Button(renderer, menuFont, "NEW GAME", 300, 300, 80, 50);
	//loadGame = new Button(renderer, menuFont, "LOAD GAME", 400, 300, 80, 50);

	//newGame->init();
	//loadGame->init();
	btn = new AnimatedButton(renderer, { 400 - 100,304 - 100,80, 60 }, "PLAY", btnFont);
	btn->init();
	init3D();
	//menuSurface = IMG_Load("assets/menu_back.jpg");

	//if (menuSurface == nullptr) std::cout << "menuSurface is null \n";

	//menuTexture = SDL_CreateTextureFromSurface(renderer, menuSurface);
	//if (menuTexture == nullptr) std::cout << "menu texture is null" << std::endl;
}

int Menu::handleMenuEvents(SDL_Event& e) {
	btn->handleUserMouseMotion(e);
	/*if (newGame->handleUserActions(e)) {
		return 1;
	}
	else if (loadGame->handleUserActions(e)) {
		return 2;
	}*/
	return 0;
}

void Menu::render() {
	// std::cout << "start menu render" << std::endl;
	//static SDL_Rect menuRect = { 0, 0, 800, 600 };
	//SDL_RenderCopy(renderer, menuTexture, NULL, &menuRect);
	//newGame->render();
	//loadGame->render();

	background();
	btn->render();
}

void Menu::background() {
	last = now;
	now = SDL_GetTicks();
	gameFrame(deltaTime, cubes, &cubesLength);
	draw(renderer);
	drawCubes(renderer, cubes, cubesLength);
	deltaTime = (double)((now - last)) / 12000;
}

void Menu::init3D() {
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	now = 0;
	last = 0;
	deltaTime = 0;
	cubesLength = 0;
	gameInit(cubes, &cubesLength);
}