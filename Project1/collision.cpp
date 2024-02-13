#include "collision.h"

Collision::Collision(std::vector<std::vector<int>> collider) {

	/**
	* constructor
	*/

	std::cout << "collision class constructor called" << std::endl;
	this->collider = collider;
}

Collision::~Collision() {

	/**
	* destructor
	*/

	std::cout << "collision class destructor called" << std::endl;
}