#include "entity.h"

SDL_Texture* Entity::vessel = nullptr;

Entity::Entity(SDL_Renderer* renderer) : renderer(renderer) {
	//constructor
	std::cout << "Entity constructor initialize" << std::endl;
}

Entity::~Entity() {
	//destructor
}

void Entity::init() {
	setLocation();
	setProtocol();
	setProtocolCode();
}

void Entity::render() {
	SDL_RenderCopy(renderer, vessel, NULL, &desRect);
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

int Entity::getLayer() {
	return position.y + desRect.h;
}

Uint32 Entity::getProtocolCode() {
	return code;
}

void Entity::setTexture(std::string path, SDL_Renderer* renderer) {
	Entity::vessel = TextureManagement::LoadTexture(path, renderer);
}

void Entity::setLocation() {
	position.x = Math::Casuale::casuale(0, 50) * TILE_WIDTH;
	position.y = Math::Casuale::casuale(0, 50) * TILE_WIDTH;

	desRect = { 0,0, 32, 91 };
}

void Entity::setX() {
	position.x = 54 * 32;
	position.y = 30 * 32;
}