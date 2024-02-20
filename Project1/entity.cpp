#include "entity.h"

Entity::Entity(SDL_Renderer* renderer) : renderer(renderer) {
	//constructor
	std::cout << "Entity constructor initialize" << std::endl;
}

Entity::~Entity() {
	//destructor
}

void Entity::init() {
	//default
}

void Entity::render() {
	//default
}

void Entity::free() {
	//default
}

void Entity::updateLocation(int x_, int y_) {
	x = x_;
	y = y_;
}

void Entity::getLocation(SDL_Rect object) {
	x = object.x + (object.w / 2);
	y = object.y + object.h;
}

void Entity::setLocation(int map_x, int map_y) {
	//esRect = { (((12 - 2) * TILE_WIDTH) + (TILE_WIDTH / 2) + (OBJECT_WIDTH / 2)), ((9 * TILE_HEIGHT) + TILE_HEIGHT - OBJECT_HEIGHT) - 10, OBJECT_WIDTH, OBJECT_HEIGHT };

}