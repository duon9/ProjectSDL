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

bool Collision::cameraCollision(int& next_map_x, int& next_map_y) {

	// if false the object will move else the camera move;

	if (next_map_x + MAX_VIEW_BLOCK_HORIZONTAL > map_width || next_map_x - MAX_VIEW_BLOCK_HORIZONTAL < 0 || next_map_y + MAX_VIEW_BLOCK_VERTICAL > map_height || next_map_y - MAX_VIEW_BLOCK_VERTICAL < 0) {
		return false;
	}
}

bool Collision::isCenterHorizontal(SDL_Rect& desRect) {
	return true;
}

bool Collision::isCenterVertical(SDL_Rect& desRect){
	return true;
}