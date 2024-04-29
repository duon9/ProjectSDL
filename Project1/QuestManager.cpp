#include "QuestManager.h"
#include "constant.h"

void QuestManager::init() {
	addNode();
}

void QuestManager::addNode() {
	Node* temp = new Node();
	temp->data.content.push_back("Kill 5 Skeleton at Greyyard \n   Progress: ");
	temp->data.name = "Newbie's adventure";
	temp->data.object = "skeleton";
	temp->data.number = 5;
	temp->data.finish = false;
	temp->next = nullptr;
	first = temp;
	last = temp;
}

Node* QuestManager::getMission() {
	return first;
}

void QuestManager::check(std::string type) {
	if (first->data.finish == true) return;
	if (first->data.object == type) {
		first->data.progress += 1;
		if (first->data.progress == first->data.number) {
			first->data.finish = true;
			first->data.content.clear();
			first->data.content.push_back("Excellent kid, you can do it by yourseft");
			first->data.content.push_back("Most of adventurer die when do their first mission");
			first->data.content.push_back("Come back here in tomorrow to take your next \n  mission");
		}
	}
}