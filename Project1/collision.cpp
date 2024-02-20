#include "collision.h"

Collision::Collision(std::vector<std::vector<int>> collider) {

	/**
	* constructor
	*/

	std::cout << "collision class constructor called" << std::endl;
	this->collider = collider;
	this->map_width = collider[0].size();
	this->map_height = collider.size();
}

Collision::~Collision() {

	/**
	* destructor
	*/

	std::cout << "collision class destructor called" << std::endl;
}
