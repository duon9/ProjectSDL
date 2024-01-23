#include "test.h"
#include <random>

Test::Test() {
}

Test::~Test() {
}

void Test::run() {
	init();
	initChar();
	gameLoop();
}

void Test::gameLoop() {
	while (true) {
		handleEvents();
		render();
	}
}

void Test::init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG);
	IMG_Init(IMG_INIT_PNG);

	win = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
	ren = SDL_CreateRenderer(win, -1, 0);

	src.x = 0;
	src.y = 2 * 64;
	des.x = des.y = 0;
	src.w = 64;
	src.h = 64;

	des.w = 96;
	des.h = 96;

	//----------------------------------------------

	//SDL_Rect re;
	for (int i = 0; i < 7; i++) {
		east_clips[i] = { i * 64, 6 * 64, 64, 64 };
		west_clips[i] = { i * 64, 7 * 64, 64, 64 };
		south_clips[i] = { i * 64, 4 * 64, 64 ,64 };
		north_clips[i] = {i * 64, 5 * 64, 64, 64};
	}
}

void Test::render() {
	SDL_RenderClear(ren);

	renBack();
	renChar();

	SDL_RenderPresent(ren);
	SDL_Delay(1000 / 60);
	
}

bool quit;

void Test::handleEvents() {
	SDL_Event e;
	SDL_PollEvent(&e);
	switch (e.type) {
	case SDL_QUIT:
		break;
	case SDL_KEYDOWN:
		switch (e.key.keysym.scancode) {
		case SDL_SCANCODE_A:
		case SDL_SCANCODE_LEFT:
			orient = Orient::WEST;
			objectState = charState::RUNNING;
			des.x-=2;
			break;
		case SDL_SCANCODE_W:
		case SDL_SCANCODE_UP:
			orient = Orient::NORTH;
			objectState = charState::RUNNING;
			des.y-=2;
			break;
		case SDL_SCANCODE_S:
		case SDL_SCANCODE_DOWN:
			orient = Orient::SOUTH;
			objectState = charState::RUNNING;
			des.y+=2;
			break;
		case SDL_SCANCODE_D:
		case SDL_SCANCODE_RIGHT:
			orient = Orient::EAST;
			objectState = charState::RUNNING;
			des.x+= 2;
			break;
		}
		break;
	case SDL_KEYUP:
		if (orient == Orient::EAST && (e.key.keysym.scancode == SDL_SCANCODE_D || e.key.keysym.scancode == SDL_SCANCODE_RIGHT)) {
			objectState = charState::STANDING;
			frameCount = 0;
		}
		else if (orient == Orient::WEST && (e.key.keysym.scancode == SDL_SCANCODE_A || e.key.keysym.scancode == SDL_SCANCODE_LEFT)) {
			objectState = charState::STANDING;
			frameCount = 0;
		}
		else if (orient == Orient::SOUTH && (e.key.keysym.scancode == SDL_SCANCODE_S || e.key.keysym.scancode == SDL_SCANCODE_DOWN)) {
			objectState = charState::STANDING;
			frameCount = 0;
		}
		else if (orient == Orient::NORTH && (e.key.keysym.scancode == SDL_SCANCODE_W || e.key.keysym.scancode == SDL_SCANCODE_UP)) {
			objectState = charState::STANDING;
			frameCount = 0;
		}
		break;
	}
}

// TO DO: fix the 

void Test::renChar() {
	//TextureManagement::Draw(ren, tex, src, des);


	if (objectState == charState::STANDING) {
		if (orient == 0) {
			src.x = 0;
			src.y = 64;
		}
		else if (orient == 1) {
			src.x = 0;
			src.y = 3 * 64;
		}
		else if (orient == 3) {
			src.x = 0;
			src.y = 0;
		}
		else if (orient == 2) {
			src.x = 0;
			src.y = 2 * 64;
		}
	}
	else if (objectState == charState::RUNNING) {

		frameCount++;

		if (frameCount == 60) frameCount = 0;

		int k = frameCount / 10;

		switch (orient) {
		case Orient::EAST:
			src = east_clips[k];
			break;
		case Orient::NORTH:
			src = north_clips[k];
			break;
		case Orient::SOUTH:
			src = south_clips[k];
			break;
		case Orient::WEST:
			src = west_clips[k];
			break;
		}
	}
	
	TextureManagement::Draw(ren, tex, src, des);
}

void Test::renBack() {
	for (int i = 0; i < 38; i++) {
		for (int j = 0; j < 50; j++) {
			mapDes.x = i * 16;
			mapDes.y = j * 16;
			switch (map[i][j]) {
			case 100:
				TextureManagement::Draw(ren, grass, mapSrc, mapDes);
				break;
			case 101:
				TextureManagement::Draw(ren, wall, mapSrc, mapDes);
				break;
			}
		}
	}
}

void Test::initChar() {
	std::string path = "assets/characters/human2.png";
	tex = TextureManagement::LoadTexture(path, ren);

	if (tex == nullptr) {
		std::cout << "null tex" << std::endl;
	}
	grass = TextureManagement::LoadTexture("assets/.tile/grass.png", ren);
	test = TextureManagement::LoadTexture(TEST, ren);
	wall = TextureManagement::LoadTexture(TEST1, ren);

	if (test == nullptr) {
		std::cout << "null back" << std::endl;
	}

	map = Map::loadMap("assets/map/test.txt");
	mapSrc.x = mapSrc.y = 0;
	mapDes.x = mapDes.y = 0;
	mapSrc.w = mapSrc.h = 16;
	mapDes.w = mapDes.h = 64;
}

void Test::baseAttack() {
}

void Test::runEast() {
}