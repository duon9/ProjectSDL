#include "collision.h"

std::vector<std::vector<int>> Collision::collider;
int Collision::map_width;
int Collision::map_height;

Collision::Collision(SDL_Rect* object, SDL_Rect* camera, SDL_Point *position) {

	/**
	* constructor
	*/
	this->object = object;
	this->position = position;
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
	if (center->x /*- object->w / 2*/ + velo_x < 0 || center->y + velo_y < 0) return true;
	if (center->x /*+ object->w / 2*/ + velo_x >= map_width * TILE_WIDTH || center->y + velo_y >= map_height * TILE_HEIGHT) return true;
	if (collider[(center->y + velo_y) / TILE_HEIGHT][(center->x + velo_x) / TILE_WIDTH] == 0 /*|| collider[(center->y + velo_y) / TILE_HEIGHT][(center->x - object->w / 2 + velo_x) / TILE_WIDTH] == 0 || collider[(center->y + velo_y) / TILE_HEIGHT][(center->x + object->w / 2 + velo_x) / TILE_WIDTH] == 0*/) return true;
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

void Collision::reload() {
	map_width = collider[0].size();
	map_height = collider.size();
	//this->collider = collider;
}

bool Collision::rectCollidingVertical(SDL_Rect object1, SDL_Rect object2) {
	int left_a = object1.x;
	int right_a = object1.x + object1.w;
	int top_a = object1.y;
	int bottom_a = object1.y + object1.h;

	int left_b = object2.x;
	int right_b = object2.x + object2.w;
	int top_b = object2.y;
	int bottom_b = object2.y + object2.h;

	// Check if object1 is between top and bottom of object2 vertically
	if ((top_a > top_b && top_a < bottom_b) || (bottom_a > top_b && bottom_a < bottom_b)) {
		// Check if left or right side of object1 collides with object2
		if ((left_a > left_b && left_a < right_b) || (right_a > left_b && right_a < right_b)) {
			return true;
		}
	}

	// Check if object2 is between top and bottom of object1 vertically
	if ((top_b > top_a && top_b < bottom_a) || (bottom_b > top_a && bottom_b < bottom_a)) {
		// Check if left or right side of object2 collides with object1
		if ((left_b > left_a && left_b < right_a) || (right_b > left_a && right_b < right_a)) {
			return true;
		}
	}

	return false;
}

SDL_Point Collision::atBlock() {
	return {0,0};
}

void Collision::update(SDL_Point point, int value) {
	if (point.x < map_width && point.y < map_height && point.x >= 0 && point.y >= 0) {
		Collision::collider[point.x][point.y] = value;
	}
	//Collision::collider[point.x][point.y] = 0;
}

int Collision::getWidth() {
	return map_width;
}

int Collision::getHeight() {
	return map_height;
}

bool Collision::check(SDL_Point position, SDL_Rect object) {
	SDL_Point* center = new SDL_Point();
	center->x = position.x + object.w / 2;
	center->y = position.y + object.h - static_cast<int>(TOLERANCE * object.h);
	if (collider[(center->y) / TILE_HEIGHT][(center->x) / TILE_WIDTH] == 0) return true;
	delete center;
	return false;
}