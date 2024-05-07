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

int QuestManager::getCurrentQuest() {
	/*
	* this function is used to get the current quest index
	*/
	return curr;
}

int QuestManager::getCurrentProgress() {
	/*
	* this function is used to get the current progress of current quest
	*/

	return quests[curr].progress;
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

void QuestManager::setMission(int mission) {
	curr = mission;
}

void QuestManager::setProgress(int progress) {
	quests[curr].progress = progress;
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
	mission1.content.push_back("This is your first mission \n    Reported that the dark has come back in the greyyard");
	mission1.content.push_back("at the west side of the Pearl Harbor, use HolySpear to\n    purify them");
	mission1.content.push_back("Kill 5 Skeleton at Greyyard \n   Progress: ");
	mission1.name = "Newbie's adventure";
	mission1.object = "skeleton";
	mission1.number = 5;
	mission1.finish = false;

	//Quest mission1;
	Quest mission2;
	mission2.content.push_back("Well done kid, most of adventurer cannot survive in their \n   first mission");
	mission2.content.push_back("Due to the drastically exploit coal underground, the slime \n    do not have inhabitant, so they have took over our sewer");
	mission2.content.push_back("Go to underground to eliminate them");
	mission2.content.push_back("Slime has become an digust problem for citizen in \n   Pearl Harbor, you have to eliminate them");
	mission2.content.push_back("Kill 10 Slime under the Pearl Harbor\n   Progress: ");
	mission2.finish = false;
	mission2.name = "Digusting odd";
	mission2.number = 10;
	mission2.object = "slime";
	quests.push_back(mission1);
	quests.push_back(mission2);

	Quest mission3;
	mission3.content.push_back("Congratulations, you have done a great job");
	mission3.content.push_back("Now, come to the next job, we will uprank to bronze \n    after this mission");
	mission3.content.push_back("Reported that under the city has skeleton mace you \n   have to clear them in order to protect the researcher");
	mission3.content.push_back("Kill 8 Mace Skeleton under the Pearl Harbor\n   Progress: ");
	mission3.finish = false;
	mission3.name = "Digusting odd";
	mission3.number = 8;
	mission3.object = "mace";
	quests.push_back(mission3);

	Quest mission4;
	mission4.content.push_back("Congratulations, you have done a great job");
	mission4.content.push_back("Now, come to the next job, Hashashin, one of gold\n    rank advanturer, have a request to kill the fireworm at");
	mission4.content.push_back("arrakis, this is a hard mission, so you need to \n    prepare carefully");
	mission4.content.push_back("Kill the fireworm at Arrakis\n   Progress: ");
	mission4.finish = false;
	mission4.name = "Arrakis trip";
	mission4.number = 1;
	mission4.object = "fireworm";
	quests.push_back(mission4);
}