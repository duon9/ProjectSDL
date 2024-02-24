#include "collision.h"

Collision::Collision(std::vector<std::vector<int>> collider, SDL_Rect* object, SDL_Rect* camera, SDL_Point *position) {

	/**
	* constructor
	*/

	std::cout << "collision class constructor called" << std::endl;
	this->collider = collider;
	this->object = object;
	this->camera = camera;
	this->position = position;
	this->map_width = collider[0].size();
	this->map_height = collider.size();
}

Collision::~Collision() {

	/**
	* destructor
	*/

	std::cout << "collision class destructor called" << std::endl;
}

bool Collision::isCollidingHorizontal(int velocity) {
	//SDL_Point center;
	int center;
	center = position->x + object->w / 2;
	//center.y = position->y + object->h - static_cast<int>(TOLERANCE * object->h);

	if (center + velocity < 0) return true;
	if (center + camera->w / 2 + velocity > map_width * TILE_WIDTH) return true;
	return false;
}

bool Collision::isCollidingVertical(int velocity) {
	int center;
	center = position->y + object->h - static_cast<int>(TOLERANCE * object->h);
	if (center + velocity < 0) return true;
	if (center + camera->h / 2 + velocity > map_height * TILE_WIDTH) return true;
	return false;
}

bool Collision::isColliding(int velo_x, int velo_y) {
	//std::cout << "HIT collider" << std::endl;
	SDL_Point *center = new SDL_Point();
	center->x = position->x + object->w / 2;
	center->y = position->y + object->h - static_cast<int>(TOLERANCE * object->h);
	if (center->x - object->w / 2 + velo_x < 0 || center->y + velo_y < 0) return true;
	if (center->x + object->w / 2 + velo_x >= map_width * TILE_WIDTH || center->y + velo_y >= map_height * TILE_HEIGHT) return true;
	if (collider[(center->y + velo_y) / TILE_HEIGHT][(center->x + velo_x) / TILE_WIDTH] == 0) return true;
	delete[] center;
	return false;
}