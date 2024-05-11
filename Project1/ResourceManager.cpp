#include "ResourceManager.h"
#include "utils.h"
#include "global.h"

int ResourceManager::loadNPCProperties(void* data) {

	return 0;
}

int loader(void* data) {
	std::vector<std::string> types = { "npc_monk", "npc_hashashin", "npc_priestess", "npc_mauler", "npc_ranger", "npc_bladekeeper", "npc_knight", "npc_guard", "smokeTile", "wave", "receptionist", "questgiver", "mace", "fireTile", "iceTile", "slime", "obelisk", "zombie", "goblin"};
	std::vector<std::string> textures = { "assets/characters/goblin.png", "assets/characters/zombie.png","assets/characters/shield.png","assets/characters/element.png","assets/characters/slime.png","assets/characters/mace.png" };
	for (auto it = types.begin(); it != types.end(); it++) {
		//std::cout << "load finish " << *it << std::endl;
		global::stats[*it] = new Stat();
		global::frames[*it] = new std::vector<Frame>;
		global::clips[*it] = new std::vector<std::vector<SDL_Rect>>;
		File::getProperties(*it, global::stats[*it]);
		File::getFrameLimit(*it, global::frames[*it]);
		*global::clips[*it] = File::getClips(*it);
	}

	for (auto it = textures.begin(); it != textures.end(); it++) {
		if (global::resources[*it] == nullptr) {
			global::resources[*it] = TextureManagement::LoadTexture(*it, global::renderer);
		}
	}
	return 0;
}


void ResourceManager::run() {
	//std::vector<std::string> types = { "npc_monk", "npc_hashashin", "npc_priestess", "npc_mauler", "npc_ranger", "npc_bladekeeper", "npc_knight" };
	//std::string test = "npc_monk";
	int x = 10;
	thread1 = SDL_CreateThread(loader, "duongdz", (void*)x);
	//SDL_WaitThread(thread1, NULL);
}

void ResourceManager::wait() {
	SDL_WaitThread(thread1, NULL);
}