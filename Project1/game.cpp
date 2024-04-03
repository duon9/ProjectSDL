#include "game.h"

Game::Game() {
	std::cout << "Constructor Game started" << std::endl;

	global::window = nullptr;
	global::renderer = nullptr;
	screenWidth = 800;
	screenHeight = 608;
	Global::gamestate = GameState::MENU;
}

Game::~Game() {
	SDL_Quit();
}

void Game::run() {
	init("Bastard", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	gameLoop();
}

void Game::init(const char* title, int _x, int _y, int _w, int _h, Uint32 flags) {
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	global::window = SDL_CreateWindow(title, _x, _y, _w, _h, flags);
	global::renderer = SDL_CreateRenderer(global::window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);
	menu = new Menu(global::renderer);
	menu->init();
	interface = new Interface(global::renderer, map);
	interface->init();
	entitys = new EntityManager(global::renderer, &e, map, interface);
	entitys->init();
}

void Game::gameLoop() {
	while (Global::gamestate != GameState::EXIT) {
		handleEvents();
		render();
	}
}

void Game::handleEvents() {
	SDL_PollEvent(&e);
	if (Global::gamestate == GameState::MENU) {
		if (menu->handleMenuEvents(e) == 1) {
			Global::gamestate = GameState::PLAY;
			delete menu;
		}
		else if (menu->handleMenuEvents(e) == 2) {
			printf("Still updating");
		}
		else if (menu->handleMenuEvents(e) == 4) {
			Global::gamestate = GameState::EXIT;
		}
	}

	if (e.type == SDL_QUIT) {
		Global::gamestate = EXIT;
	}

	if (Global::gamestate == GameState::PLAY) {
		//player1->handleUserEvents(e);
		entitys->HandleEvents();
		//interface->handleInterfaceEvents();
	}
}

void Game::render() {
	SDL_RenderClear(global::renderer);

	switch (Global::gamestate) {
	case GameState::MENU:
		menu->render();
		break;

	case GameState::PLAY:
		interface->render();
		//player1->render();
		entitys->render();
		break;

	default:
		break;
	}
	SDL_SetRenderDrawColor(global::renderer, 0, 0, 0, 255);
	SDL_RenderPresent(global::renderer);
	FPScontroller::FPSlimit(60);
}

