
#ifndef DRAW_H
#define DRAW_H

#include <SDL.h>
#include "zGame.h"

#define WIDTH 800 // 1000
#define HEIGHT 608 // 1000
#define CUBE_SIZE 680

void draw(SDL_Renderer* renderer);

void drawCubes(SDL_Renderer* renderer, Cube cubes[], int cubesLength);

void drawCube(SDL_Renderer* renderer, Cube cube, SDL_Color gradient);

void drawSpeedText(SDL_Renderer* renderer);

void drawGameOverText(SDL_Renderer* renderer);

#endif