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

	for (int i = 0; i < 100; i++) {
		Computer* computer = new Computer(renderer, "minotaur");
		computers.push_back(computer);
	}

	for (auto& player : players) {
		player->init();
	}

	for (auto& computer : computers) {
		computer->init();
	}
}

void EntityManager::setCollision() {
	collider = File::readCollision(mapWare[*map]);
}

void EntityManager::HandleEvents() {
	for (auto& player : players) {
		player->handleUserEvents(e);
		player->handleBarDisplay();
	}

	for (auto& computer : computers) {
		computer->chaseTarget(players);
	}

	for (auto& player : players) {
		player->listen(e);
	}

	for (auto& computer : computers) {
		computer->listen(e);
	}
}

void EntityManager::render() {

	for (auto& player : players) {
		player->render();
	}

	for (auto& computer : computers) {
		if (isInScreen(interface->camera, computer->getRect())) {
			//std::cout << "bot is in rect" << std::endl;
			//computer->updateObjectScreenPosition(&interface->camera);
			interface->updateObjectScreenPosition(computer->position, computer->desRect);
			computer->render();
		}
		else {
			//std::cout << "bot is not in rect" << std::endl;
		}
	}
}

bool EntityManager::isInScreen(SDL_Rect object1, SDL_Rect object2) {
	return Collision::rectColliding(object1, object2);
}