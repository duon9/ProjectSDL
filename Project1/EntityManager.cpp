#include "EntityManager.h"

#define COMPUTER_CODE 101
#define MAX_PLAYER_COUNT 1
#define MAX_MINOTAUR_COUNT 0
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
	Portal::loadClip();
	Portal::loadTexture();
	Little::vessel = TextureManagement::LoadTexture("assets/characters/rogue2.png", renderer);
	Minotaur::vessel = TextureManagement::LoadTexture("assets/characters/minotaur.png", renderer);
	NightBorne::vessel = TextureManagement::LoadTexture("assets/characters/NightBorne.png", renderer);
	Player::vessel = TextureManagement::LoadTexture("assets/characters/little.png", renderer);
	Skeleton::vessel = TextureManagement::LoadTexture("assets/characters/skeleton.png", renderer);
	FireWorm::vessel = TextureManagement::LoadTexture("assets/characters/fireworm.png", renderer);
	player = new Player(renderer, "little", interface);
	player->init();
	layers.push_back(player);
	 
	setComputer();
}

void EntityManager::HandleEvents() {

	if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_f) {
		if (map == GREYYARD) {
			clean();
			//setComputer();
			Object::collider = File::readCollision(water_town);
			setComputer();

			interface->reload(TEST);
			player->reload();
			map = LIBRARY;
		}
		else {
			clean();
			//setComputer();
			Object::collider = File::readCollision(grey);
			setComputer();

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
	player->handleLogic();

	for (auto& computer : computers) {
		computer->listen(e);
		computer->handleLogic();
	}

	for (auto& teleporter : global::teleporters) {
		if (teleporter->isTeleport(player->getEntityCenterPoint())) {
			if (map == teleporter->getCurrentMap()) {
				clean();
				map = teleporter->getDestination();
				//setComputer();
				Object::collider = File::readCollision(teleporter->getColliderPath());
				interface->reload(teleporter->getInterfacePath());
				player->reload();
				player->setLocation(teleporter->getDestinationPoint());
				setComputer();
			}
		}
	}

	for (auto& npc : npcs) {
		npc->listen(&global::e);
	}

	for (auto& object : global::missles) {
		if (object->getCollideState()) {
			continue;
		}
		else object->projectile();
		for (auto& entity : layers) {
			if (entity->getProtocolCode() == object->getProtocolCode() || entity->check_death == true) continue;
			else {
				object->handleEffect(entity->getRect());
				if (object->getCollideState() == true) {
					entity->handleMissle(object->getDamage());
					break;
				}
			}
		}
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
			else {
				//entity->desRect.x = -1000;
				//entity->desRect.y = -1000;
			}
		}
		else {
			entity->render();
		}
	}

	for (auto& object : global::missles) {
		interface->updateObjectScreenPosition(object->position, object->desRect);
		object->render(); // error
	}

	for (auto& teleporter : global::teleporters) {
		/*interface->updateObjectScreenPosition(teleporter->position, teleporter->desRect);
		teleporter->render();*/
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

	/*for (auto& teleporter : global::teleporters) {
		delete teleporter;
	}*/
	global::missles.clear();
	global::teleporters.clear();
	for (int i = 0; i < (int)computers.size(); i++) {
		delete computers[i];
	}
	computers.clear();

	for (int i = 0; i < (int)npcs.size(); i++) {
		delete npcs[i];
	}
	npcs.clear();
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

	/*for (int i = 0; i < MAX_MINOTAUR_COUNT; i++) {
		Minotaur* computer = new Minotaur(renderer);
		computer->init();
		computers.push_back(computer);
		layers.push_back(computer);
	}*/
	if (map == TAVERN) {
		Guard* guard = new Guard(renderer);
		guard->init();
		guard->setLocation({ 15 * 32, 15 * 32 });
		layers.push_back(guard);
		npcs.push_back(guard);

		for (int i = 0; i < 0; i++) {
			Skeleton* li = new Skeleton(renderer);
			li->init();
			li->setLocation({ 20 * 32,20 * 32 });
			computers.push_back(li);
			layers.push_back(li);
		}
	}
	else {
		for (int i = 0; i < 100; i++) {
			Skeleton* li = new Skeleton(renderer);
			li->init();
			computers.push_back(li);
			layers.push_back(li);
		}
		for (int i = 0; i < 0; i++) {
			NightBorne* li = new NightBorne(renderer);
			li->init();
			computers.push_back(li);
			layers.push_back(li);
		}
		for (int i = 0; i < 0; i++) {
			FireWorm* li = new FireWorm(renderer);
			li->init();
			computers.push_back(li);
			layers.push_back(li);
		}

	}

	if (map == LIBRARY) {
		Teleporter* teleporter = new Teleporter(renderer);
		teleporter->init();
		teleporter->setMap(Map::LIBRARY);
		teleporter->setColliderPath(grey);
		teleporter->setDestination(Map::GREYYARD);
		teleporter->setDestinationPoint({ 916,615 });
		teleporter->setInterfacePath(greyyard);
		teleporter->setLocation({ -90,6 * 32 });
		global::teleporters.push_back(teleporter);
	}
	else if (map == GREYYARD) {
		Teleporter* teleporter = new Teleporter(renderer);
		teleporter->init();
		teleporter->setMap(Map::GREYYARD);
		teleporter->setColliderPath(water_town);
		teleporter->setDestination(Map::LIBRARY);
		teleporter->setDestinationPoint({ 0,6 * 32 });
		teleporter->setInterfacePath(TEST);
		teleporter->setLocation({ 950,589 });
		global::teleporters.push_back(teleporter);

		Teleporter* teleporter2 = new Teleporter(renderer);
		teleporter2->init();
		teleporter2->setMap(Map::GREYYARD);
		teleporter2->setColliderPath(tavern_collision);
		teleporter2->setDestination(Map::TAVERN);
		teleporter2->setDestinationPoint({ 594 + 22,904 });
		teleporter2->setInterfacePath(tavern_interface);
		teleporter2->setLocation({ -90,10 * 32 });
		global::teleporters.push_back(teleporter2);

		Portal* portal = new Portal();
		portal->init();
		portal->setMap(Map::GREYYARD);
		portal->setColliderPath(tavern_collision);
		portal->setDestination(Map::TAVERN);
		portal->setDestinationPoint({ 594 + 22,904 });
		portal->setInterfacePath(tavern_interface);
		portal->setLocation({ 705, 195 });
		global::teleporters.push_back(portal);
		layers.push_back(portal);
	}
	else if (map == TAVERN) {
		Teleporter* teleporter = new Teleporter(renderer);
		teleporter->init();
		teleporter->setMap(Map::TAVERN);
		teleporter->setColliderPath(grey);
		teleporter->setDestination(Map::GREYYARD);
		teleporter->setDestinationPoint({ 0,350 });
		teleporter->setInterfacePath(greyyard);
		teleporter->setLocation({ 592 + 16, 900 + 30 });
		teleporter->setSize(32, 32);
		global::teleporters.push_back(teleporter);
	}
}
