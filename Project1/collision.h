#pragma once
#include <vector>
#include <iostream>
#include "constant.h"

class Collision
{
public:
	void init();
	Collision(std::vector<std::vector<int>> collider);
	~Collision();
	bool cameraCollision(int& next_map_x, int& next_map_y);
	bool isCenterHorizontal(SDL_Rect& desRect);
	bool isCenterVertical(SDL_Rect& desRect);

private:
	int map_width, map_height;
	std::vector<std::vector<int>> collider;
};
