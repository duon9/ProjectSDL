#include "zGame.h"

#include <SDL.h>
#include <math.h>
#include "zMath.h"

const float PLAYER_INITIAL_SPEED = 200;
const float BASE_TURN_SPEED = 30;

const int CUBE_AMOUNT = 100; // number of cube appear on screen in one second

const unsigned long cubeMemSize = CUBE_POINTS_N * sizeof(Point); // size of Point is 4(float) * 3, so cube memSize  = 20 * 12 = 240pixel

const float MAX_DEPTH = 150;
const float BOUNDS_X = 12;
const float BOUNDS_Y = 12;
const float SPEED_INCREASE = 0; // speed increase, hmm

const float CUBE_SIZE = 0.5; // cube size, suggest not modify as it cause lag

float playerSpeed; // assigned at line 45

void addNewCube(Cube cubes[], int* cubesLength) {
    //create Cube on screen, we transmit array of cube, and cube length
    Point p = {
        .x = randF(-BOUNDS_X, BOUNDS_X),
        .y = randF(-BOUNDS_Y, BOUNDS_Y),
        .z = MAX_DEPTH,
    };
    Cube cube = newCube(p, CUBE_SIZE); // add cube
    cubes[(*cubesLength)++] = cube;
}

void addInitialCube(Cube cubes[], int* cubesLength) {
    Point p = {
        .x = randF(-BOUNDS_X, BOUNDS_X),
        .y = randF(-BOUNDS_Y, BOUNDS_Y),
        .z = randF(0, MAX_DEPTH),
    };
    Cube cube = newCube(p, CUBE_SIZE);
    cubes[(*cubesLength)++] = cube;
}

void gameInit(Cube cubes[], int* cubesLength) {
    playerSpeed = PLAYER_INITIAL_SPEED; // assign value for playerSpeed
    while ((*cubesLength) < CUBE_AMOUNT) {
        addInitialCube(cubes, cubesLength);
    }
}

void removeCube(Cube cubes[], int i) { // free pointer and delete by pointing to null
    free(cubes[i]);
    cubes[i] = NULL;
}

void rearrangeCubesToTakeOutRemoved(Cube cubes[], int* cubesLength, int removedN) {
    // rearrange the cube array, such as vector
    if (removedN == 0) {
        return;
    }

    int fullI = 0;
    for (int i = 0; i < (*cubesLength); i++) {
        if (cubes[i] != NULL) {
            cubes[fullI++] = cubes[i]; // if cubes[i] = null, the loop continue, so fullI will smaller the i, in next time, the cubes[fullI] = cubes[i]
        }
    }
}

void flipCubeIfOutOfBounds(Cube cubes[], int i) {

    // check if the block fly out of screen, rearrange them in screen

    if (cubes[i][0].x < -BOUNDS_X) {
        for (int p = 0; p < 20; p++) {
            cubes[i][p].x += BOUNDS_X * 2;
        }
    }
    else if (cubes[i][0].x > BOUNDS_X) {
        for (int p = 0; p < 20; p++) {
            cubes[i][p].x -= BOUNDS_X * 2;
        }
    }
    if (cubes[i][0].y < -BOUNDS_Y) {
        for (int p = 0; p < 20; p++) {
            cubes[i][p].y += BOUNDS_X * 2;
        }
    }
    else if (cubes[i][0].y > BOUNDS_Y) {
        for (int p = 0; p < 20; p++) {
            cubes[i][p].y -= BOUNDS_Y * 2;
        }
    }
}

int compareSize(const void* a, const void* b) {

    /*
    * campare location of Cube
    * if cube1 < cube2, return will be a negative number
    * if cube1 = cube2, return 0
    * if cube1 > cube2, return a positive number
    */

    Cube cube1 = *((Cube*)a);  // casting void* to Cube*, then get the value of pointer
    Cube cube2 = *((Cube*)b);
    if (cube1[0].z == cube2[0].z) {
        return (cube1[0].x < cube2[0].x) - (cube1[0].x > cube2[0].x);
    }
    return (cube1[0].z < cube2[0].z) - (cube1[0].z > cube2[0].z);
}

int gameFrame(float deltaTime, Cube cubes[], int* cubesLength) {
    // main member of gameloop
    while (*cubesLength < CUBE_AMOUNT) { // if the current cubes < CUBE_AMOUNT, add newCubes inorder to 
        addNewCube(cubes, cubesLength); // add cube
    }

    float speed = playerSpeed  * deltaTime;
    float turnSpeed = (BASE_TURN_SPEED + playerSpeed / 50) * deltaTime;

    playerSpeed += deltaTime * SPEED_INCREASE; // increase velocity base on time

    int cubesRemoved = 0; // reset cubeRemoved variable

    const Uint8* keyState = SDL_GetKeyboardState(NULL);

    float xDiff = 0;
    float yDiff = 0;
    if (keyState[SDL_SCANCODE_W]) {
        yDiff = +turnSpeed;
    }
    if (keyState[SDL_SCANCODE_S]) {
        yDiff = -turnSpeed;
    }
    if (keyState[SDL_SCANCODE_A]) {
        xDiff = +turnSpeed;
    }
    if (keyState[SDL_SCANCODE_D]) {
        xDiff = -turnSpeed;
    }
    float zSpeed = -speed;
    if (keyState[SDL_SCANCODE_LSHIFT]) {
        zSpeed *= 10;
    }

    for (int i = 0; i < (*cubesLength); i++) {
        if ((cubes[i][0].z + zSpeed) < 1.5) { // if cube is away 1.5 pixel from the screen remove cube and update the cubeRemoved(int)
            removeCube(cubes, i);
            cubesRemoved += 1;
        }
        else { // if not, check if the cubes has deviated from the XY boundary, relocate it;
            flipCubeIfOutOfBounds(cubes, i);
            for (int p = 0; p < 20; p++) { // relocate 20 vertex of Cubes, 
                cubes[i][p].x += xDiff;
                cubes[i][p].y += yDiff;

                cubes[i][p].z += zSpeed;
            }

            float middleX = fabs(cubes[i][0].x + (cubes[i][2].x - cubes[i][0].x) / 2); // fabs(num) return the absolute value of float number
            float middleY = fabs(cubes[i][0].y + (cubes[i][2].y - cubes[i][0].y) / 2);
            if (cubes[i][0].z < 2 && middleX < 0.5 && middleY < 0.5) {
                return 0;
            }
        }
    }

    rearrangeCubesToTakeOutRemoved(cubes, cubesLength, cubesRemoved); // eliminate out of screen cubes

    *cubesLength -= cubesRemoved; // update the number of cubes in array

    qsort(cubes, *cubesLength, sizeof(Cube*), compareSize); // sort the array base on location of each Cubes

    return 0; // if success return 0
}

Cube newCube(Point c, float s) {
    //Create 20 vertex of cube
    float half = s / 2.0; //s -> size, c -> location to spawn cube

    Cube cubeAddr;
    cubeAddr = malloc(cubeMemSize);

    // Up
    Point u1 = { .x = -half + c.x, .y = -half + c.y, .z = +half * 2 + c.z };
    Point u2 = { .x = +half + c.x, .y = -half + c.y, .z = +half * 2 + c.z };
    Point u3 = { .x = +half + c.x, .y = -half + c.y, .z = -half + c.z };
    Point u4 = { .x = -half + c.x, .y = -half + c.y, .z = -half + c.z };

    // Down
    Point d1 = { .x = -half + c.x, .y = +half + c.y, .z = +half * 2 + c.z };
    Point d2 = { .x = +half + c.x, .y = +half + c.y, .z = +half * 2 + c.z };
    Point d3 = { .x = +half + c.x, .y = +half + c.y, .z = -half + c.z };
    Point d4 = { .x = -half + c.x, .y = +half + c.y, .z = -half + c.z };

    // Left
    Point l1 = { .x = -half + c.x, .y = +half + c.y, .z = +half * 2 + c.z };
    Point l2 = { .x = -half + c.x, .y = -half + c.y, .z = +half * 2 + c.z };
    Point l3 = { .x = -half + c.x, .y = -half + c.y, .z = -half + c.z };
    Point l4 = { .x = -half + c.x, .y = +half + c.y, .z = -half + c.z };

    // Right
    Point r1 = { .x = +half + c.x, .y = +half + c.y, .z = +half * 2 + c.z };
    Point r2 = { .x = +half + c.x, .y = -half + c.y, .z = +half * 2 + c.z };
    Point r3 = { .x = +half + c.x, .y = -half + c.y, .z = -half + c.z };
    Point r4 = { .x = +half + c.x, .y = +half + c.y, .z = -half + c.z };

    // Front
    Point f1 = { .x = -half + c.x, .y = -half + c.y, .z = -half + c.z };
    Point f2 = { .x = +half + c.x, .y = -half + c.y, .z = -half + c.z };
    Point f3 = { .x = +half + c.x, .y = +half + c.y, .z = -half + c.z };
    Point f4 = { .x = -half + c.x, .y = +half + c.y, .z = -half + c.z };

    cubeAddr[0] = u1;
    cubeAddr[1] = u2;
    cubeAddr[2] = u3;
    cubeAddr[3] = u4;

    cubeAddr[4] = d1;
    cubeAddr[5] = d2;
    cubeAddr[6] = d3;
    cubeAddr[7] = d4;

    cubeAddr[8] = l1;
    cubeAddr[9] = l2;
    cubeAddr[10] = l3;
    cubeAddr[11] = l4;

    cubeAddr[12] = r1;
    cubeAddr[13] = r2;
    cubeAddr[14] = r3;
    cubeAddr[15] = r4;

    cubeAddr[16] = f1;
    cubeAddr[17] = f2;
    cubeAddr[18] = f3;
    cubeAddr[19] = f4;

    return cubeAddr;
}