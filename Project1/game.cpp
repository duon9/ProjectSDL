#include "game.h"

Game::Game() {
	std::cout << "Constructor Game started" << std::endl;

	window = nullptr;
	renderer = nullptr;
	screenWidth = 800;
	screenHeight = 600;
	gamestate = GameState::MENU;
}

Game::~Game() {
	SDL_Quit();
}

void Game::run() {
	init("Bastard", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	gameLoop();
}

void Game::init(const char* title, int _x, int _y, int _w, int _h, Uint32 flags) {
	std::cout << "start initialize Game class" << std::endl;

	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	window = SDL_CreateWindow(title, _x, _y, _w, _h, flags);
	renderer = SDL_CreateRenderer(window, -1, 0);
	menu = new Menu(renderer);
	menu->init();
	interface = new Interface(renderer);
	interface->init();
	player1 = new Player(renderer, ROGUE);
	player1->init();
}

void Game::gameLoop() {
	std::cout << "start gameLoop() Game class" << std::endl;
	while (gamestate != GameState::EXIT) {
		handleEvents();
		render();
	}
}

void Game::handleEvents() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (gamestate == GameState::MENU) {
			if (menu->handleMenuEvents(e) == 1) {
				gamestate = GameState::PLAY;
				delete(menu);
			}
			else if (menu->handleMenuEvents(e) == 2) {
				printf("Still updating");
			}
		}

		if (gamestate == GameState::PLAY) {
			player1->handleUserEvents(e);
		}
	}
}

void Game::render() {
	SDL_RenderClear(renderer);

	switch (gamestate) {
	case GameState::MENU:
		menu->render();
		break;

	case GameState::PLAY:
		interface->render();
		player1->render();
		break;

	default:
		break;
	}

	SDL_RenderPresent(renderer);
	SDL_Delay(1000 / 240);
}