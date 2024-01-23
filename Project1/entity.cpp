#include "entity.h"

Entity::Entity(SDL_Renderer* renderer) : renderer(renderer) {
	//constructor
}

Entity::~Entity() {
	//destructor
}

Orient Entity::getOrient() {
	return curr_orient;
}

blockPosition Entity::getBlockPos() {
	return currBlockPos;
}

void Entity::updateOrient(Orient tmpOrient) {
	curr_orient = tmpOrient;
}

void Entity::updateBlockPos(blockPosition tmpBlockPos) {
	currBlockPos = tmpBlockPos;
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