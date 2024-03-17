#pragma once
#include <vector>
#include <iostream>
#include "constant.h"

class Collision
{
public:
	void init();
	bool isCollidingHorizontal(int velocity);
	bool isCollidingVertical(int velocity);
	bool isColliding(int velo_x, int velo_y);
	static bool rectColliding(SDL_Rect object1, SDL_Rect object2);
	static bool rectCollidingVertical(SDL_Rect object1, SDL_Rect object2);
	void reload(std::vector<std::vector<int>> collider);
	Collision(std::vector<std::vector<int>> collider, SDL_Rect* object, SDL_Rect* camera, SDL_Point* position);
	~Collision();


private:
	int map_width, map_height;
	std::vector<std::vector<int>> collider;

	SDL_Rect* object;
	SDL_Point* position;
};
