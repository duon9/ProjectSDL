#include "EntityManager.h"

EntityManager::EntityManager(SDL_Renderer* renderer, SDL_Event e) {
	this->renderer = renderer;
	this->e = e;
	std::cout << "EntityManager constructor called \n";
}

EntityManager::~EntityManager() {
	std::cout << "EntityManager destructor called \n";
}