#include "menu.h"
#include "zMath.h"
#include "zDraw.h"
#include "zGame.h"
#include <iostream>

Menu::Menu(SDL_Renderer* renderer) : renderer(renderer) {
	std::cout << "Constructor Menu started" << std::endl;
}

// delete menu

Menu::~Menu() {
	TTF_CloseFont(menuFont);
	TTF_CloseFont(headerFont);
	delete btn;
	delete load;
	delete tutorial;
	delete exit;
	delete header;
	delete tutorialwindow;
	delete music;
	std::cout << "Constructor Menu free" << std::endl;
}

void Menu::init() {
	//std::cout << "start Menu initialize" << std::endl;
	menuFont = TTF_OpenFont("assets/fonts/test.ttf", 20);
	//btnFont = TTF_OpenFont(font2.c_str(), 20);
	headerFont = TTF_OpenFont(font2.c_str(), 120);
	tutorialwindow = new Tutorial(renderer, menuFont);
	load = new AnimatedButton(renderer, { 400 + 50,304,160, 60 }, "LOAD", menuFont);
	btn = new AnimatedButton(renderer, { 400 - 160 - 50, 304, 160, 60 }, "PLAY", menuFont);
	tutorial = new AnimatedButton(renderer, { 400 - 160 - 50, 304 + 30 + 60,160, 60 }, "TUTORIAL", menuFont);
	exit = new AnimatedButton(renderer, { 400 + 50, 304 + 30 + 60, 160, 60 }, "EXIT", menuFont);
	music = new SFX();
	earth = new EarthPlanet(renderer);
	music->add("assets/audio/music-game.wav");
	header = new Header(renderer, "Bastard", headerFont);
	btn->init();
	load->init();
	earth->init();
	tutorial->init();
	exit->init();
	header->init();
	tutorialwindow->init();
	
	init3D();
	music->play();
}

int Menu::handleMenuEvents(SDL_Event& e) {

	if (isOpen) {
		if (tutorialwindow->handleEvents(e)) {
			isOpen = false;
			return 0;
		}
	}
	else {
		if (btn->handleUserMouseMotion(e)) {
			return 1;
		}
		if (load->handleUserMouseMotion(e)) {
			return 2;
		}
		if (tutorial->handleUserMouseMotion(e)) {
			isOpen = true;
			return 0;
		}
		if (exit->handleUserMouseMotion(e)) {
			return 4;
		}
	}
	return 0;
}

void Menu::render() {

	background();
	if (isOpen) {
		//std::cout << "isopne" << std::endl;
		tutorialwindow->render();
	}
	else {
		btn->render();
		load->render();
		tutorial->render();
		exit->render();
		header->render();
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Menu::background() {
	earth->render();
	/*last = now;
	now = SDL_GetTicks();
	gameFrame(deltaTime, cubes, &cubesLength);
	draw(renderer);
	drawCubes(renderer, cubes, cubesLength);
	deltaTime = (double)((now - last)) / 12000;*/
}

void Menu::init3D() {
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	now = 0;
	last = 0;
	deltaTime = 0;
	cubesLength = 0;
	gameInit(cubes, &cubesLength);
}