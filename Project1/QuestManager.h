#pragma once
#include <iostream>
#include <vector>

struct Quest {
	std::string name;
	std::string object;
	int number;
	std::vector<std::string> content;
	int progress;
	bool finish = false;
	Quest() {
		progress = 0;
	}
};

struct Node {
	Node* next;
	Quest data;
};

class QuestManager
{
private:
	Node* first = nullptr;
	Node* last = nullptr;
	Node* trash = nullptr;
	std::vector<Quest> quests;
	int curr = 0;
	QuestManager() {
		init();
	}

	QuestManager(const QuestManager&) = delete;
	QuestManager& operator=(const QuestManager&) = delete;
public:
	static QuestManager& getInstance() {
		static QuestManager instance;
		return instance;
	}
	void addMission();
	void init();
	void addNode(Quest data);
	void check(std::string type);
	//void deleteMission();
	Quest getMission();
};

