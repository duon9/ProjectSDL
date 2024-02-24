#include "EntityManager.h"

EntityManager::EntityManager(SDL_Renderer* renderer, SDL_Event *e, Map* map, Interface* interface) {
	this->renderer = renderer;
	this->e = e;
	this->map = map;
	this->interface = interface;
	std::cout << "EntityManager constructor called \n";
}

EntityManager::~EntityManager() {
	std::cout << "EntityManager destructor called \n";
}

void EntityManager::init() {
	for (int i = 0; i < 1; i++) {
		Player* player = new Player(renderer, ROGUE, interface);
		players.push_back(player);
	}
	setCollision();
}

void EntityManager::setCollision() {
	collider = File::readCollision(mapWare[*map]);
}