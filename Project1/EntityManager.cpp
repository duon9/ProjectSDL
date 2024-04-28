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

	Collision::collider = File::readCollision(grey);
	Collision::reload();
	Portal::loadClip();
	Portal::loadTexture();
	player = new Player(renderer, "little", interface);
	player->init();
	global::layers.push_back(player);
	 
	setComputer();
}

void EntityManager::HandleEvents() {

	player->handleUserEvents(e);
	//player->handleBarDisplay();

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
				Collision::collider = File::readCollision(teleporter->getColliderPath());
				Collision::reload();
				interface->reload(teleporter->getInterfacePath());
				player->setLocation(teleporter->getDestinationPoint());
				setComputer();
				global::lighthouse.clear();
				setMapLogic();
			}
		}
	}

	for (auto object : global::dtiles) {
		object->handleEvents();
		object->handleLogic();
	}

	for (auto& npc : npcs) {
		npc->listen(&global::e);
		npc->update();
	}

	for (auto& object : global::missles) {
		if (object->getCollideState()) {
			continue;
		}
		else object->projectile();
		for (int i = 0; i < global::layers.size(); i++) {
			if (global::layers[i]->getProtocolCode() == object->getProtocolCode() || global::layers[i]->getProtocolCode() == 30 || global::layers[i]->check_death == true) continue;
			else {
				object->handleEffect(global::layers[i]->getRect());
				if (object->getCollideState() == true) {
					//std::cout << "this is why we start" << std::endl;
					global::layers[i]->handleMissle(object->getDamage(), object->getEffect());
					break;
				}
			}
		}
	}

	player->handleBarDisplay();
}

void EntityManager::render() {


	sortLayer();
	for (const auto& entity : global::layers) {
		if (entity->getProtocolCode() == COMPUTER_CODE || entity->getProtocolCode() == 99 || entity->getProtocolCode() == 30) {
			if (isInScreen(interface->camera, entity->getRect())) {
				interface->updateObjectScreenPosition(entity->position, entity->desRect);
				entity->render();
			}
			else {
				entity->desRect.x = -1000;
				entity->desRect.y = -1000;
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
	int n = global::layers.size();
	for (int i = 1; i < n; i++) { 
		Entity* key = global::layers[i];
		int j = i - 1;

		while (j >= 0 && global::layers[j]->getLayer() > key->getLayer()) { 
			global::layers[j + 1] = global::layers[j];
			j -= 1;
		}
		global::layers[j + 1] = key;
	}
}

void EntityManager::reload() {
	Object::collider = File::readCollision(water_town);
}

void EntityManager::clean() {

	/*for (auto& teleporter : global::teleporters) {
		delete teleporter;
	}*/
	global::dtiles.clear();
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
	for (int i = 0; i < (int)global::layers.size(); i++)
	{
		if (global::layers[i]->getProtocolCode() == 99) {
			delete global::layers[i];
		}
	}
	global::layers.clear();
	global::layers.push_back(player);
}

void EntityManager::setComputer() {

	if (map == GREYYARD) {
		Obelisk* obelisk = new Obelisk(global::renderer);
		obelisk->init();
		obelisk->setLocation({ 320, 320 });
		global::layers.push_back(obelisk);
		npcs.push_back(obelisk);
	}


	if (map == TAVERN) {
		Guard* guard = new Guard(renderer);
		guard->init();
		guard->setLocation({ 15 * 32, 15 * 32 });
		global::layers.push_back(guard);
		npcs.push_back(guard);

	

		for (int i = 0; i < 0; i++) {
			Skeleton* li = new Skeleton(renderer);
			li->init();
			li->setLocation({ 20 * 32,20 * 32 });
			computers.push_back(li);
			global::layers.push_back(li);
		}
	}
	else {
		for (int i = 0; i < 0; i++) {
			Skeleton* li = new Skeleton(renderer);
			li->init();
			computers.push_back(li);
			global::layers.push_back(li);
		}
		for (int i = 0; i < 0; i++) {
			NightBorne* li = new NightBorne(renderer);
			li->init();
			computers.push_back(li);
			global::layers.push_back(li);
		}
		for (int i = 0; i < 1; i++) {
			FireWorm* li = new FireWorm(renderer);
			li->init();
			computers.push_back(li);
			global::layers.push_back(li);
		}

		for (int i = 0; i < 0; i++) {
			Computer* li = new Computer(global::renderer, "wizard");
			li->init();
			computers.push_back(li);
			global::layers.push_back(li);
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

		for (int i = 0; i < 10; i++) {
			MaceSkeleton* li = new MaceSkeleton(renderer);
			li->init();
			computers.push_back(li);
			global::layers.push_back(li);
		}

		// 1153 1040

		for (int i = 0; i < 10; i++) {
			Fire* fire = new Fire(global::renderer);
			fire->setLocation({ 1153, 1040 });
			fire->setLumination();
			global::dtiles.push_back(fire);
			global::layers.push_back(fire);

		}
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
		portal->setColliderPath(arrakis_collider);
		portal->setDestination(Map::SAND);
		portal->setDestinationPoint({ 672, 428 });
		portal->setInterfacePath(arrakis);
		portal->setLocation({ 705, 195 });
		global::teleporters.push_back(portal);
		global::layers.push_back(portal);
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
	else if (map == Map::SAND) {
		Portal* portal = new Portal();
		portal->init();
		portal->setMap(Map::SAND);
		portal->setColliderPath(grey);
		portal->setDestination(Map::GREYYARD);
		portal->setDestinationPoint({ 13 * 32, 10 * 32 });
		portal->setInterfacePath(greyyard);
		portal->setLocation({ 100, 100 });
		global::teleporters.push_back(portal);
		global::layers.push_back(portal);
	}
}

void EntityManager::setMapLogic() {
	if (map == LIBRARY) {
		global::isDark = true;
	}
	else {
		global::isDark = false;
	}
	if (map == TAVERN) {
		global::isHaveArcane = false;
	}
	else {
		global::isHaveArcane = true;
	}

}