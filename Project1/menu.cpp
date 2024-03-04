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
	menuFont = TTF_OpenFont("assets/fonts/test.ttf", 20);
	btnFont = TTF_OpenFont(font2.c_str(), 20);
	headerFont = TTF_OpenFont(font2.c_str(), 120);
	if (menuFont == nullptr) std::cout << "menu font is null " << std::endl;

	load = new AnimatedButton(renderer, { 400 + 50,304,160, 60 }, "LOAD", menuFont);
	btn = new AnimatedButton(renderer, { 400 - 160 - 50, 304, 160, 60 }, "PLAY", menuFont);
	tutorial = new AnimatedButton(renderer, { 400 - 160 - 50, 304 + 30 + 60,160, 60 }, "TUTORIAL", menuFont);
	exit = new AnimatedButton(renderer, { 400 + 50, 304 + 30 + 60, 160, 60 }, "EXIT", menuFont);
	header = new Header(renderer, "Bastard", headerFont);
	btn->init();
	load->init();
	tutorial->init();
	exit->init();
	header->init(); 
	
	init3D();

}

int Menu::handleMenuEvents(SDL_Event& e) {
	if (btn->handleUserMouseMotion(e)) {
		return 1;
	}
	if (load->handleUserMouseMotion(e)) {
		return 2;
	}
	if (tutorial->handleUserMouseMotion(e)) {
		return 3;
	}
	if (exit->handleUserMouseMotion(e)) {
		return 4;
	}
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
	load->render();
	tutorial->render();
	exit->render();
	header->render();
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