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

void Entity::setProtocolCode() {
	code = 99;
}

void Entity::setProtocol() {
	protocol = new Protocol(code);
}

SDL_Point Entity::getPosition() {
	return position;
}

SDL_Rect Entity::getRect() {
	return { position.x, position.y, desRect.w, desRect.h };
}