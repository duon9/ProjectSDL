#include "dialogue_box.h"

void DialogueBox::add(std::string content) {
	dialogue.push_back(content);
}

void DialogueBox::show() {
	isShow = true;
	std::cout << dialogue[currDialogue] << std::endl;
}

void DialogueBox::next() {
	if (isShow) {
		std::cout << dialogue[++currDialogue];
	}
}