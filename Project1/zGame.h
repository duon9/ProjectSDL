#pragma once

#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <stdio.h>
#define CUBE_FACE_POINTS_N 4
#define CUBE_FACE_N 5
#define CUBE_POINTS_N 20  // 5 face * 4 point each face so 5 * 4 = 20
#define FRONT_I 16        // 4 * 4

extern float playerSpeed;

//typedef struct {
//	float z;
//} Player;

typedef struct Point {
	float x;
	float y;
	float z;
} Point;

//struct Block {
//	printf("hello");
//};

typedef Point* Cube;

int gameFrame(float deltaTime, Cube cubes[], int* cubesLength);

void gameInit(Cube cubes[], int* cubesLength);

Cube newCube(Point c, float s);

#endif