#pragma once
#include <vector>
#include <iostream>

class Collision
{
public:
	void init();
	Collision(std::vector<std::vector<int>> collider);
	~Collision();

private:
	std::vector<std::vector<int>> collider;
};
