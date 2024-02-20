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


private:
	int map_width, map_height;
	std::vector<std::vector<int>> collider;
};
