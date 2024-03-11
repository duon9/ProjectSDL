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
		player->init();
		players.push_back(player);
		layers.push_back(player);
	}
	// 
	for (int i = 0; i < 1; i++) {
		Computer* computer = new Computer(renderer, "minotaur");
		computer->init();
		computers.push_back(computer);
		layers.push_back(computer);
	}

	//for (auto& player : players) {
	//	player->init();
	//}

	//for (auto& computer : computers) {
	//	computer->init();
	//}
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
	sortLayer();
	for (const auto& entity : layers) {
		if (typeid(entity) == typeid(Computer*)) {
			if (isInScreen(interface->camera, entity->getRect())) {
				interface->updateObjectScreenPosition(entity->position, entity->desRect);
				entity->render();
			}
			else {
				entity->render();
			}
		}
	}

	/*for (auto& player : players) {
		player->render();
	}

	for (auto& computer : computers) {
		if (isInScreen(interface->camera, computer->getRect())) {
			interface->updateObjectScreenPosition(computer->position, computer->desRect);
			computer->render();
		}
	}*/

	//typeid()

}

bool EntityManager::isInScreen(SDL_Rect object1, SDL_Rect object2) {
	return Collision::rectColliding(object1, object2);
}

bool EntityManager::compare(Entity* a, Entity* b) {
	return a->getLayer() > b->getLayer();
}

void EntityManager::sortLayer() {
	int n = layers.size();
	for (int i = 0; i < n; i++) {
		Entity* key = layers[i];
		int j = i + 1;

		while (j >= 0 && layers[j]->getLayer() < key->getLayer()) {
			layers[j + 1] = layers[j];
			j -= 1;
		}
		layers[j + 1] = key;
	}
}