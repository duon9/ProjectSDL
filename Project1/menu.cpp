#include "menu.h"

#include <iostream>

Menu::Menu(SDL_Renderer* renderer) : renderer(renderer) {
	std::cout << "Constructor Menu started" << std::endl;
}

Menu::~Menu() {
	SDL_FreeSurface(menuSurface);
	SDL_DestroyTexture(menuTexture);
}

void Menu::init() {
	std::cout << "start Menu initialize" << std::endl;
	menuFont = TTF_OpenFont("assets/fonts/test.ttf", 14);
	if (menuFont == nullptr) std::cout << "menu font is null " << std::endl;

	newGame = new Button(renderer, menuFont, "NEW GAME", 300, 300, 80, 50);
	loadGame = new Button(renderer, menuFont, "LOAD GAME", 400, 300, 80, 50);

	newGame->init();
	loadGame->init();

	menuSurface = IMG_Load("assets/menu_back.jpg");

	if (menuSurface == nullptr) std::cout << "menuSurface is null \n";

	menuTexture = SDL_CreateTextureFromSurface(renderer, menuSurface);
	if (menuTexture == nullptr) std::cout << "menu texture is null" << std::endl;
}

int Menu::handleMenuEvents(SDL_Event& e) {
	if (newGame->handleUserActions(e)) {
		return 1;
	}
	else if (loadGame->handleUserActions(e)) {
		return 2;
	}
}

void Menu::render() {
	// std::cout << "start menu render" << std::endl;
	static SDL_Rect menuRect = { 0, 0, 800, 600 };
	SDL_RenderCopy(renderer, menuTexture, NULL, &menuRect);
	newGame->render();
	loadGame->render();
}