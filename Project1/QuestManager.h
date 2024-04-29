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
	QuestManager() {
		init();
	}
public:
	static QuestManager& getInstance() {
		static QuestManager instance;
		return instance;
	}
	void init();
	void addNode();
	void check(std::string type);
	void deleteMission();
	Node* getMission();
};

