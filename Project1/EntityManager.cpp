#include "EntityManager.h"

#define COMPUTER_CODE 101
#define MAX_PLAYER_COUNT 1
#define MAX_MINOTAUR_COUNT 1
#define MAX_COLUMN_COUNT 10

EntityManager::EntityManager(SDL_Renderer* renderer, SDL_Event *e, Map* map, Interface* interface) {
	this->renderer = renderer;
	this->e = e;
	this->interface = interface;
	std::cout << "EntityManager constructor called \n";
}

EntityManager::~EntityManager() {
	std::cout << "EntityManager destructor called \n";
}

void EntityManager::init() {

	Object::collider = File::readCollision(grey);

	Player::texture = TextureManagement::LoadTexture("assets/characters/rogue2.png", renderer);

	player = new Player(renderer, ROGUE, interface);
	player->init();
	layers.push_back(player);
	 
	setComputer();

	//Entity::setTexture("assets/characters/test.png", renderer);
	//for (int i = 0; i < MAX_COLUMN_COUNT; i++) {
	//	Entity* ent = new Entity(renderer);
	//	ent->init();
	//	layers.push_back(ent);
	//}

	//Entity* ens = new Entity(renderer);
	//ens->init();
	//ens->setLocation({54*32,30*32});
	//layers.push_back(ens);
}

void EntityManager::HandleEvents() {

	if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_f) {
		if (map == GREYYARD) {
			clean();
			setComputer();
			Object::collider = File::readCollision(water_town);
			interface->reload(TEST);
			player->reload();
			map = LIBRARY;
		}
		else {
			clean();
			setComputer();
			Object::collider = File::readCollision(grey);
			interface->reload(greyyard);
			player->reload();
			map = GREYYARD;
		}
	}

	player->handleUserEvents(e);
	player->handleBarDisplay();

	for (auto& computer : computers) {
		computer->chaseTarget(player);
	}

	player->listen(e);

	for (auto& computer : computers) {
		computer->listen(e);
	}
}

void EntityManager::render() {
	//std::sort(layers.begin(), layers.end(), compare);
	sortLayer();
	for (const auto& entity : layers) {
		if (entity->getProtocolCode() == COMPUTER_CODE || entity->getProtocolCode() == 99) {
			if (isInScreen(interface->camera, entity->getRect())) {
				interface->updateObjectScreenPosition(entity->position, entity->desRect);
				entity->render();
			}
		}
		else {
			entity->render();
		}
	}
}

bool EntityManager::isInScreen(SDL_Rect object1, SDL_Rect object2) {
	return Collision::rectColliding(object1, object2);
}


void EntityManager::sortLayer() {
	int n = layers.size();
	for (int i = 1; i < n; i++) { 
		Entity* key = layers[i];
		int j = i - 1;

		while (j >= 0 && layers[j]->getLayer() > key->getLayer()) { 
			layers[j + 1] = layers[j];
			j -= 1;
		}
		layers[j + 1] = key;
	}
}

void EntityManager::reload() {
	Object::collider = File::readCollision(water_town);
}

void EntityManager::clean() {
	for (int i = 0; i < (int)computers.size(); i++) {
		delete computers[i];
	}
	computers.clear();

	for (int i = 0; i < (int)layers.size(); i++)
	{
		if (layers[i]->getProtocolCode() == 99) {
			delete layers[i];
		}
	}
	layers.clear();
	layers.push_back(player);
}

void EntityManager::setComputer() {
	for (int i = 0; i < MAX_MINOTAUR_COUNT; i++) {
		Computer* computer = new Computer(renderer, "minotaur");
		computer->init();
		computers.push_back(computer);
		layers.push_back(computer);
	}
}