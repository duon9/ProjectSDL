#include "collision.h"

Collision::Collision(std::vector<std::vector<int>> collider, SDL_Rect* object, SDL_Rect* camera, SDL_Point *position) {

	/**
	* constructor
	*/

	std::cout << "collision class constructor called" << std::endl;
	this->collider = collider;
	this->object = object;
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
	SDL_Point* center = new SDL_Point();
	center->x = position->x + object->w / 2;
	center->y = position->y + object->h - static_cast<int>(TOLERANCE * object->h);
	if (center->x - object->w / 2 + velocity < 0) return true;
	if (center->x + object->w / 2 + velocity > map_width * TILE_WIDTH) return true;
	if (collider[(center->y) / TILE_HEIGHT][(center->x + velocity) / TILE_WIDTH] == 0) return true;
	delete center;
	return false;
}

bool Collision::isCollidingVertical(int velocity) {
	SDL_Point* center = new SDL_Point();
	center->x = position->x + object->w / 2;
	center->y = position->y + object->h - static_cast<int>(TOLERANCE * object->h);
	if (center->y + velocity < 0) return true;
	if (center->y + velocity > map_height * TILE_WIDTH) return true;
	if (collider[(center->y + velocity) / TILE_HEIGHT][(center->x) / TILE_WIDTH] == 0) return true;
	delete center;
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
	delete center;
	return false;
}

bool Collision::rectColliding(SDL_Rect object1, SDL_Rect object2) {
	int left_a = object1.x;
	int right_a = object1.x + object1.w;
	int top_a = object1.y;
	int bottom_a = object1.y + object1.h;

	int left_b = object2.x;
	int right_b = object2.x + object2.w;
	int top_b = object2.y;
	int bottom_b = object2.y + object2.h;

	// Case 1: size object 1 < size object 2
	if (left_a > left_b && left_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}
	}

	if (left_a > left_b && left_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}

	// Case 2: size object 1 < size object 2
	if (left_b > left_a && left_b < right_a)
	{
		if (top_b > top_a && top_b < bottom_a)
		{
			return true;
		}
	}

	if (left_b > left_a && left_b < right_a)
	{
		if (bottom_b > top_a && bottom_b < bottom_a)
		{
			return true;
		}
	}

	if (right_b > left_a && right_b < right_a)
	{
		if (top_b > top_a && top_b < bottom_a)
		{
			return true;
		}
	}

	if (right_b > left_a && right_b < right_a)
	{
		if (bottom_b > top_a && bottom_b < bottom_a)
		{
			return true;
		}
	}

	// Case 3: size object 1 = size object 2
	if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
	{
		return true;
	}

	return false;
}