#include "zDraw.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <math.h>
#include <stdbool.h>
#include "zGame.h"
#include "zMath.h"

const int UP = 0; // using enum instead
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;
const int FRONT = 4;

const int BACKGROUND_R = 255; // back ground color 15 255 155
const int BACKGROUND_G = 255;
const int BACKGROUND_B = 255;

int TRANSFORMED_FRONT_I = 4 * 5;

SDL_Point transformedCube[CUBE_FACE_N * 5]; // CUBE_FACE_N the number of face of a cube, in this case is five( we cannot see the back of cube)

SDL_Color darkBackgroundTriangle = { .r = 0, .b = 0, .g = 0, .a = 250 / 3 }; // -> 0 0 0 250/3
SDL_Color emptyBackgroundTriangle = { .r = 255, .b = 255, .g = 255, .a = 0 }; //-> 255 255 255 0
SDL_Color white = { .r = 255, .g = 255, .b = 255, .a = 255 };
TTF_Font* Sans = NULL; // font
SDL_Color TEXT_COLOR = { 0, 0, 0 }; // text color

void drawBackgroundTriangle(SDL_Renderer* renderer, SDL_FPoint trianglePoints[]) {
    // draw triangle
    SDL_Vertex triangle[3];
    triangle[0].position = trianglePoints[0];
    triangle[1].position = trianglePoints[1];
    triangle[2].position = trianglePoints[2];
    triangle[0].color = darkBackgroundTriangle;
    triangle[1].color = emptyBackgroundTriangle;
    triangle[2].color = darkBackgroundTriangle;
    SDL_RenderGeometry(renderer, NULL, triangle, 3, NULL, 0);
}

void draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, BACKGROUND_R, BACKGROUND_G, BACKGROUND_B, 255);
    SDL_FPoint triangle1Points[] = {
        {.x = -WIDTH, .y = HEIGHT / 2},
        {.x = WIDTH / 2, .y = -HEIGHT},
        {.x = WIDTH * 2, .y = HEIGHT / 2},
    };
    SDL_FPoint triangle2Points[] = {
        {.x = -WIDTH, .y = HEIGHT / 2},
        {.x = WIDTH / 2, .y = HEIGHT * 2},
        {.x = WIDTH * 2, .y = HEIGHT / 2},
    };

    SDL_RenderClear(renderer);
    drawBackgroundTriangle(renderer, triangle1Points);
    drawBackgroundTriangle(renderer, triangle2Points);
}

float screenX(float x) {
    //return x * WIDTH + WIDTH / 2;
    return x * CUBE_SIZE + CUBE_SIZE / 2;
}

float screenY(float y) {
    return y * CUBE_SIZE + CUBE_SIZE / 2;
}

bool isPointOutsideFront(int f, int frontI) {
    // check if point is outside screen
    float x = transformedCube[f].x;
    float y = transformedCube[f].y;
    float frontStartX = transformedCube[frontI].x;
    float frontEndX = transformedCube[frontI + 2].x;
    float frontStartY = transformedCube[frontI].y;
    float frontEndY = transformedCube[frontI + 2].y;
    bool outWithX = x < frontStartX || x > frontEndX;
    bool outWithY = y < frontStartY || y > frontEndY;
    return outWithX || outWithY;
}

void drawCubes(SDL_Renderer* renderer, Cube cubes[], int cubesLength) {
    //drawcubes
    for (int i = 0; i < cubesLength; i++) {

        SDL_Color color = { .r = 255 , .g = 255, .b = 255, .a = 0};
        drawCube(renderer, cubes[i], color);
    }
}

float fadeTowards(float current, float target, float amount) {
    if (current == target) {
        return current;
    }
    float toDiff = fabs((current - target) * amount);
    if (current > target) {
        return current - toDiff;
    }
    else {
        return current + toDiff;
    }
}

void drawCube(SDL_Renderer* renderer, Cube cube, SDL_Color gradient) {
    for (int f = 0; f < 5; f++) { // f mean faces, in these case is 5 faces(front, up down, left, right)
        int orgCubeI = f * 4;    // The way our cube is defined, a face has four cornes
        int transCubeI = f * 5;  // The way our transformed cube is defined, a face has 5 corners (last one connects back to the firt one)
        for (int p = 0; p < 4; p++) {
            Point point = cube[orgCubeI + p]; // problem here
            SDL_Point sPoint = { screenX(transform3Dto2D(point.x, point.z)), screenY(transform3Dto2D(point.y, point.z)) };
            transformedCube[transCubeI + p] = sPoint;
        }
        transformedCube[transCubeI + 4] = transformedCube[transCubeI + 0];
    }
    // If a have has at least two points outside of front, it gets to be drawn last
    int faceOrder[5];

    int lastI = 4;
    int firstI = 0;

    faceOrder[lastI--] = FRONT;  // Front always gets to be last

    for (int f = 0; f < 4; f++) {
        int cubeI = f * 5;
        bool sideOutsideFront = isPointOutsideFront(cubeI, FRONT * 5) && isPointOutsideFront(cubeI + 1, FRONT * 5);
        // If we are outside, we should draw this as last as possible
        if (sideOutsideFront) {
            faceOrder[lastI--] = f;
        }
        else {
            faceOrder[firstI++] = f;
        }
    }

    // No need to draw the first 2 faces. They are hidden behind the front
    for (int f = 2; f < 5; f++) {
        int cubeI = faceOrder[f] * 5;

        SDL_FPoint triable1Points[] = {
            {.x = transformedCube[cubeI + 0].x, .y = transformedCube[cubeI + 0].y},
            {.x = transformedCube[cubeI + 1].x, .y = transformedCube[cubeI + 1].y},
            {.x = transformedCube[cubeI + 2].x, .y = transformedCube[cubeI + 2].y},
        };

        SDL_FPoint triable2Points[] = {
            {.x = transformedCube[cubeI + 2].x, .y = transformedCube[cubeI + 2].y},
            {.x = transformedCube[cubeI + 3].x, .y = transformedCube[cubeI + 3].y},
            {.x = transformedCube[cubeI + 4].x, .y = transformedCube[cubeI + 4].y},
        };

        SDL_Color color;
        
        if (f == FRONT) {
            //SDL_Color c = { .r = 255, .b = 255, .g = 255, .a = 0};
            SDL_Color c = { .r = gradient.r, .b = gradient.g, .g = gradient.b, .a = 0 };
            color = c;
        }
        else {
            SDL_Color c = { .r = gradient.r, .b = gradient.g, .g = gradient.b, .a = 0 };
            color = c;
        }

        float min = 150;
        float max = 190;

        float z = (cube[(cubeI / 5) * 4].z) + fabs(cube[(cubeI / 5) * 4].x) * 7 + fabs(cube[(cubeI / 5) * 4].y) * 7;
        float fadeAmount = z < min ? 0 : fmin((z - min) / (max - min), 1);

        color.r = color.r;
        color.g = color.g;
        color.b = color.b;
        color.a = fadeTowards(255, 0, fadeAmount);

        SDL_Vertex triangle1[3];
        SDL_Vertex triangle2[3];

        triangle1[0].color = color; // set equal to color if revert
        triangle1[1].color = color;
        triangle1[2].color = color;
        triangle2[0].color = color;
        triangle2[1].color = color;
        triangle2[2].color = color;

        triangle1[0].position = triable1Points[0];
        triangle1[1].position = triable1Points[1];
        triangle1[2].position = triable1Points[2];

        triangle2[0].position = triable2Points[0];
        triangle2[1].position = triable2Points[1];
        triangle2[2].position = triable2Points[2];

        SDL_Point linePoints[] = {
            transformedCube[cubeI + 0],
            transformedCube[cubeI + 1],
            transformedCube[cubeI + 2],
            transformedCube[cubeI + 3],
            transformedCube[cubeI + 4],
        };

        SDL_RenderGeometry(renderer, NULL, triangle1, 3, NULL, 0);
        SDL_RenderGeometry(renderer, NULL, triangle2, 3, NULL, 0);
        fadeAmount = fmin(fadeAmount * 1.5, 1);
        SDL_SetRenderDrawColor(renderer, 60, 60, 60, fadeTowards(255, 0, fadeAmount)); //color of edge here;
        SDL_RenderDrawLines(renderer, linePoints, 5);
    }
}

void drawSpeedText(SDL_Renderer* renderer) {
    if (Sans == NULL) {
        Sans = TTF_OpenFont("Mono.ttf", 42);
    }
    char score[10];
    //sprintf(score, "%d", (int)playerSpeed);
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, score, TEXT_COLOR);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_Rect Message_rect;
    Message_rect.x = 0;
    Message_rect.y = -10;
    Message_rect.w = 24 * 3;
    Message_rect.h = 50;
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
}

void drawGameOverText(SDL_Renderer* renderer) {
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "GAME OVER", TEXT_COLOR);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_Rect Message_rect;
    Message_rect.w = 600;
    Message_rect.h = 150;
    Message_rect.x = WIDTH / 2 - Message_rect.w / 2;
    Message_rect.y = HEIGHT / 2 - Message_rect.h / 2 - 10;
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
}