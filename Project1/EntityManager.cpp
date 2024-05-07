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
void EntityManager::save() {
	// save game
	File::writeSaveGame(
		player->getHealth(),
		player->getMana(),
		player->getExp(),
		player->getPosition(),
		quest.getCurrentQuest(),
		quest.getCurrentProgress(),
		map
	);
}

void EntityManager::load() {
	SDL_Point p = { 0,0 };
	File::readSaveGame(player->getStat(), p, map, quest);
	clean();
	if (map == LIBRARY) {
		Collision::collider = File::readCollision(water_town);
		interface->reload(TEST);
	}
	else if (map == GREYYARD) {
		Collision::collider = File::readCollision(grey);
		interface->reload(greyyard);
	}
	else if (map == PEARL_HARBOR) {
		Collision::collider = File::readCollision(city_collision);
		interface->reload(city_interface);
	}
	else if (map == TAVERN) {
		Collision::collider = File::readCollision(tavern_collision);
		interface->reload(tavern_interface);
	}
	else if (map == SAND) {
		Collision::collider = File::readCollision(arrakis_collider);
		interface->reload(arrakis);
	}
	Collision::reload();
	player->setLocation(p);
	setComputer();
	setMapLogic();
}

void EntityManager::init() {
	manager.run();
	Collision::collider = File::readCollision(grey);
	Collision::reload();
	Portal::loadClip();
	Portal::loadTexture();
	player = new Player(renderer, "little", interface);
	player->init();
	global::layers.push_back(player);
	global::resources["assets/characters/element.png"] = TextureManagement::LoadTexture("assets/characters/element.png", renderer);
	setComputer();
	setMapLogic();
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

	for (int i = 0; i < (int)global::teleporters.size(); i++){
		if (global::teleporters[i]->isTeleport(player->getEntityCenterPoint())) {
			if (map == global::teleporters[i]->getCurrentMap()) {
				//clean();
				map = global::teleporters[i]->getDestination();
				Collision::collider = File::readCollision(global::teleporters[i]->getColliderPath());
				Collision::reload();
				interface->reload(global::teleporters[i]->getInterfacePath());
				player->setLocation(global::teleporters[i]->getDestinationPoint());
				clean();
				setComputer();
				//global::lighthouse.clear();
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
	for (int i = 0; i < (int)global::layers.size(); i++) {
		if (global::layers[i]->getProtocolCode() == COMPUTER_CODE || global::layers[i]->getProtocolCode() == 99 || global::layers[i]->getProtocolCode() == 30) {
			if (isInScreen(interface->camera, global::layers[i]->getRect())) {
				interface->updateObjectScreenPosition(global::layers[i]->position, global::layers[i]->desRect);
				global::layers[i]->render();
			}
			else {
				global::layers[i]->desRect.x = -1000;
				global::layers[i]->desRect.y = -1000;
			}
		}
		else {
			global::layers[i]->render();
		}
	}

	for (auto& object : global::missles) {
		interface->updateObjectScreenPosition(object->position, object->desRect);
		object->render(); 
	}

	/*for (auto& teleporter : global::teleporters) {
		interface->updateObjectScreenPosition(teleporter->position, teleporter->desRect);
		teleporter->render();
	}*/

	SDL_SetRenderDrawColor(renderer, 15, 15, 15, 255);
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

	for (int i = 0; i < (int)global::lighthouse.size(); i++) {
		delete global::lighthouse[i];
	}

	global::lighthouse.clear();

	for (int i = 0; i < (int)global::dtiles.size(); i++) {
		delete global::dtiles[i];
	}
	global::dtiles.clear();

	for (int i = 0; i < (int)global::missles.size(); i++) {
		delete global::missles[i];
	}
	global::missles.clear();

	for (int i = 0; i < (int)global::teleporters.size(); i++) {
		delete global::teleporters[i];
	}
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

	if (map == PEARL_HARBOR) {
		Teleporter* teleporter = new Teleporter(renderer);
		teleporter->init();
		teleporter->setMap(Map::PEARL_HARBOR);
		teleporter->setColliderPath(grey);
		teleporter->setDestination(Map::GREYYARD);
		teleporter->setDestinationPoint({ 916,615 });
		teleporter->setInterfacePath(greyyard);
		teleporter->setLocation({ -90,17 * 32 });
		global::teleporters.push_back(teleporter);

		// 912 505

		Teleporter* teleporter2 = new Teleporter(renderer);
		teleporter2->init();
		teleporter2->setSize(32, 32);
		teleporter2->setMap(Map::PEARL_HARBOR);
		teleporter2->setColliderPath(tavern_collision);
		teleporter2->setDestination(Map::TAVERN);
		teleporter2->setDestinationPoint({ 594 + 22,904 });
		teleporter2->setInterfacePath(tavern_interface);
		teleporter2->setLocation({ 924,490 });
		global::teleporters.push_back(teleporter2);

		Teleporter* teleporter3 = new Teleporter(renderer);
		teleporter3->init();
		teleporter3->setSize(32, 32);
		teleporter3->setMap(Map::PEARL_HARBOR);
		teleporter3->setColliderPath(tavern_collision);
		teleporter3->setDestination(Map::TAVERN);
		teleporter3->setDestinationPoint({ 1090, 877 });
		teleporter3->setInterfacePath(tavern_interface);
		teleporter3->setLocation({ 1084, 490});
		global::teleporters.push_back(teleporter3);

		Teleporter* teleporter4 = new Teleporter(renderer);
		teleporter4->init();
		teleporter4->setMap(Map::PEARL_HARBOR);
		teleporter4->setColliderPath(water_town);
		teleporter4->setDestination(Map::LIBRARY);
		teleporter4->setDestinationPoint({ 0, 6 * 32 });
		teleporter4->setInterfacePath(TEST);
		teleporter4->setLocation({ 1265, 1056 });
		global::teleporters.push_back(teleporter4); // 1244 1056

		// -22 1060

		Teleporter* teleporter5 = new Teleporter(renderer);
		teleporter5->init();
		teleporter5->setMap(Map::PEARL_HARBOR);
		teleporter5->setColliderPath(water_town);
		teleporter5->setDestination(Map::LIBRARY);
		teleporter5->setDestinationPoint({ 2846, 192 });
		teleporter5->setInterfacePath(TEST);
		teleporter5->setLocation({ -22 - 60, 1060 });
		global::teleporters.push_back(teleporter5);

		Entity* ship = new Entity(renderer);
		ship->setSource(ship_source);
		ship->init();
		ship->setLocation({ 500, 600 - 32 });
		ship->setSize(256 * 1.5, 192 * 1.5);
		global::layers.push_back(ship);

		Entity* ship1 = new Entity(renderer);
		ship1->setSource(ship_source);
		ship1->init();
		ship1->setLocation({ 400, 1000 - 64 });
		ship1->setSize(256 * 2, 192 * 2);
		global::layers.push_back(ship1);

		Wave* wave = new Wave(renderer);
		wave->setLocation({ 520, 776 });
		global::layers.push_back(wave);

		damageTile* smoke = new damageTile(renderer, "smokeTile");
		smoke->init();
		smoke->setLocation({ 260, 310 });
		global::layers.push_back(smoke);
	}



	if (map == GREYYARD) {
		Obelisk* obelisk = new Obelisk(global::renderer);
		obelisk->init();
		obelisk->setLocation({ 320, 320 });
		global::layers.push_back(obelisk);
		npcs.push_back(obelisk);

		for (int i = 0; i < 5; i++) {
			Computer* zombie = new Computer(renderer, "zombie");
			zombie->init();
			global::layers.push_back(zombie);
			computers.push_back(zombie);
		}
	}


	if (map == TAVERN) {
		Guard* guard = new Guard(renderer);
		guard->init();
		guard->setLocation({ 15 * 32, 15 * 32 });
		global::layers.push_back(guard);
		npcs.push_back(guard);

		NPC* mauler = new NPC(renderer, "npc_mauler");
		mauler->init();
		mauler->setLocation({ 30 * 32, 15 * 32 });
		mauler->add("My skin is as hard as diamond");
		global::layers.push_back(mauler);
		npcs.push_back(mauler);

		NPC* ranger = new NPC(renderer, "npc_ranger");
		ranger->init();
		ranger->setLocation({ 16 * 32, 18 * 32 });
		ranger->add("let your mind flow with the wind, it will lead you\n   to the elf wood");
		global::layers.push_back(ranger);
		npcs.push_back(ranger);

		NPC* bladekeeper = new NPC(renderer, "npc_bladekeeper");
		bladekeeper->init();
		bladekeeper->setLocation({ 25 * 32, 18 * 32 });
		bladekeeper->add("my blade is the combine of blood and fire");
		global::layers.push_back(bladekeeper);
		npcs.push_back(bladekeeper);

		NPC* knight = new NPC(renderer, "npc_knight");
		knight->init();
		knight->setLocation({ 20 * 32, 15 * 32 });
		knight->add("dedicate my life to my nation");
		knight->add("you look to young to become a adventurer");
		global::layers.push_back(knight);
		npcs.push_back(knight);

		NPC* priestess = new NPC(renderer, "npc_priestess");
		priestess->init();
		priestess->setLocation({ 16 * 32, 26 * 32 });
		priestess->add("how young a kid");
		priestess->add("your eyes conceal furiosity and  desire for \n   recognization");
		global::layers.push_back(priestess);
		npcs.push_back(priestess);

		NPC* hashashin = new NPC(renderer, "npc_hashashin");
		hashashin->init();
		hashashin->setLocation({ 32 * 32, 26 * 32 });
		hashashin->add("the arrakis is my hometown");
		hashashin->add("it is covered by sand and fireworm");
		global::layers.push_back(hashashin);
		npcs.push_back(hashashin);


		NPC* monk = new NPC(renderer, "npc_monk");
		monk->init();
		monk->setLocation({ 27 * 32, 26 * 32 });
		monk->add("as silent as earth");
		monk->add("become stable in a chaotic world");
		global::layers.push_back(monk);
		npcs.push_back(monk);

	}
	if (map == GREYYARD) {
		for (int i = 0; i < 5; i++) {
			Skeleton* li = new Skeleton(renderer);
			li->init();
			computers.push_back(li);
			global::layers.push_back(li);
		}
		for (int i = 0; i < 0; i++) {
			Computer* li = new Computer(renderer, "slime");
			li->init();
			computers.push_back(li);
			global::layers.push_back(li);
		}
		for (int i = 0; i < 0; i++) {
			FireWorm* li = new FireWorm(renderer);
			li->init();
			computers.push_back(li);
			global::layers.push_back(li);
		}

		for (int i = 0; i < 0; i++) {
			Wizard* li = new Wizard(global::renderer, "wizard");
			li->init();
			computers.push_back(li);
			global::layers.push_back(li);
		}

	}

	if (map == LIBRARY) {
		Teleporter* teleporter = new Teleporter(renderer);
		teleporter->init();
		teleporter->setMap(Map::LIBRARY);
		teleporter->setColliderPath(city_collision);
		teleporter->setDestination(Map::PEARL_HARBOR);
		teleporter->setDestinationPoint({ 1240, 1056 });
		teleporter->setInterfacePath(city_interface);
		teleporter->setLocation({ -90,6 * 32 });
		global::teleporters.push_back(teleporter);

		// 2846 192

		Teleporter* teleporter2 = new Teleporter(renderer);
		teleporter2->init();
		teleporter2->setMap(Map::LIBRARY);
		teleporter2->setColliderPath(city_collision);
		teleporter2->setDestination(Map::PEARL_HARBOR);
		teleporter2->setDestinationPoint({ -22, 1055 });
		teleporter2->setInterfacePath(city_interface);
		teleporter2->setLocation({ 2866, 192 });
		global::teleporters.push_back(teleporter2);

		for (int i = 0; i < 8; i++) {
			MaceSkeleton* li = new MaceSkeleton(renderer);
			li->init();
			computers.push_back(li);
			global::layers.push_back(li);
		}

		for (int i = 0; i < 10; i++) {
			Computer* li = new Computer(renderer, "slime");
			li->init();
			computers.push_back(li);
			global::layers.push_back(li);
		}

		// 1153 1040

		for (int i = 0; i < 0; i++) {
			HealCloud* fire = new HealCloud(global::renderer);
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
		teleporter->setColliderPath(city_collision);
		teleporter->setDestination(Map::PEARL_HARBOR);
		teleporter->setDestinationPoint({ 70,18 * 32 });
		teleporter->setInterfacePath(city_interface);
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
		teleporter->setColliderPath(city_collision);
		teleporter->setDestination(Map::PEARL_HARBOR);
		teleporter->setDestinationPoint({ 910, 545 });
		teleporter->setInterfacePath(city_interface);
		teleporter->setLocation({ 592 + 16, 900 + 30 });
		teleporter->setSize(32, 32);
		global::teleporters.push_back(teleporter);

		//1074 904
		
		Teleporter* teleporter2 = new Teleporter(renderer);
		teleporter2->init();
		teleporter2->setMap(Map::TAVERN);
		teleporter2->setColliderPath(city_collision);
		teleporter2->setDestination(Map::PEARL_HARBOR);
		teleporter2->setDestinationPoint({ 1074, 545 });
		teleporter2->setInterfacePath(city_interface);
		teleporter2->setLocation({ 1084, 930 });
		teleporter2->setSize(32, 32);
		global::teleporters.push_back(teleporter2);

		Receptionist* re = new Receptionist(renderer);
		re->init();
		re->setLocation({ 25 * 32, 12 * 32 - 30 });
		global::layers.push_back(re);
		npcs.push_back(re);


		GuideGirl* gf = new GuideGirl(renderer);
		gf->init();
		gf->setLocation({ 28 * 32, 12 * 32 - 30 });
		global::layers.push_back(gf);
		npcs.push_back(gf);
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

		for (int i = 0; i < 1; i++) {
			FireWorm* li = new FireWorm(renderer);
			li->init();
			computers.push_back(li);
			global::layers.push_back(li);
		}

	}
}

void EntityManager::setMapLogic() {
	if (map == LIBRARY || map == SAND) {
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