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
