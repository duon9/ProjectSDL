#include "QuestManager.h"
#include "constant.h"

void QuestManager::init() {
	//addNode();
	//first = new Node;
	//first->data.content.push_back("Kill 5 Skeleton at Greyyard \n   Progress: ");
	//first->data.name = "Newbie's adventure";
	//first->data.object = "skeleton";
	//first->data.number = 5;
	//first->data.finish = false;
	//first->next = nullptr;
	//last = first;
	addMission();
}

void QuestManager::addNode(Quest data) {
	Node* temp = new Node;
	temp->data = data;
	temp->next = nullptr;
	last->next = temp;
	last = temp;
}

Quest QuestManager::getMission() {
	return quests[curr];
}

void QuestManager::check(std::string type) {
	//std::cout << first->data.content.at(0) << std::endl;
	//std::cout << first->data.name << std::endl;
	if (quests[curr].finish == true) {
		std::cout << "Pass" << std::endl;
		return;
	}
	if (quests[curr].object == type) {
		//std::cout << "check" << std::endl;
		quests[curr].progress += 1;
		if (quests[curr].progress == quests[curr].number) {
			//std::cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << std::endl;
			quests[curr].finish = true;
			if (curr < quests.size() - 1)curr++;

		}
	}
}

void QuestManager::addMission() {
	Quest mission1;
	mission1.content.push_back("Kill 5 Skeleton at Greyyard \n   Progress: ");
	mission1.name = "Newbie's adventure";
	mission1.object = "skeleton";
	mission1.number = 5;
	mission1.finish = false;

	//Quest mission1;
	Quest mission2;
	mission2.content.push_back("Slime has become an digust problem for citizen in \n   Pearl Harbor, you have to eliminate them");
	mission2.content.push_back("Kill 10 Slime under the Pearl Harbor\n   Progress: ");
	mission2.finish = false;
	mission2.name = "Digusting odd";
	mission2.number = 10;
	mission2.object = "slime";
	quests.push_back(mission1);
	quests.push_back(mission2);
}