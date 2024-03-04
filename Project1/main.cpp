//#include "game.h"
#include "utils.h"
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "constant.h"
#include "game.h"


int main(int argc, char* argv[])
{
	Game test;
	test.run();
	return 0;

	
	return 0;
}

//#include <SDL.h>
//#include <SDL_ttf.h>
//#include <stdbool.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//
//#include "zDraw.h"
//#include "zGame.h"
//#include "zMath.h"
//
//SDL_Window* window = NULL;
//SDL_Surface* screen = NULL;
//SDL_Renderer* renderer;
//SDL_Event e;
//bool quit = false;
//bool gameOver = false;
//
//Uint64 now = 0;
//Uint64 last = 0;
//double deltaTime = 0;
//
//int cubesLength = 0;
//Cube cubes[1000];
//
//void init() {
//    SDL_Init(SDL_INIT_EVERYTHING);
//    window = SDL_CreateWindow("Blockamok", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
//    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
//    screen = SDL_GetWindowSurface(window);
//    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
//    srand(time(NULL));
//    TTF_Init();
//    gameInit(cubes, &cubesLength);
//}
//
//void gameLoop() {
//    SDL_PollEvent(&e);
//    if (!gameOver) {
//        gameOver = gameFrame(deltaTime, cubes, &cubesLength);
//    }
//    if (e.type == SDL_QUIT) {
//        quit = true;
//    }
//}
//
//int main(int arg, char* argv[]) {
//    init();
//
//    while (!quit) {
//        last = now;
//        now = SDL_GetTicks();
//
//        gameLoop();
//
//        draw(renderer);
//
//        drawCubes(renderer, cubes, cubesLength);
//
//        //drawSpeedText(renderer);
//        //if (gameOver) {
//        //    drawGameOverText(renderer);
//        //}
//
//        SDL_RenderPresent(renderer);
//
//        deltaTime = (double)((now - last)) / 12000;
//    }
//
//    return 0;
//}