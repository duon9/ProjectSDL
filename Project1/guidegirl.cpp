#include "guidegirl.h"

void GuideGirl::listen(SDL_Event* e) {
	if (!check_pause) {
		SDL_Point point;
		bool query;
		if (protocol->receive(e, point, query)) {
			Math::Vector v = Math::Vector(getPosition(), point);
			if (v.getDistance() < 32 * 2) {
				if (box.box_target == type) {
					//std::cout << "xxxxxxxxxxxxxxxx" << std::endl;
				}
				else {
					//std::cout << "yyyyyyyyyyyyyyyy" << std::endl;
					resetDialogue();
					box.addDialogue(dialogue);
					box.box_target = "luff";
				}
				if (query) {
					box.show();
				}
				else {
					box.hide();
					box.resetContent();
					box.clear();
				}
			}
		}
	}
}

void GuideGirl::resetDialogue() {
	temp = manager.getMission();
	if (temp->data.finish == false) {
		dialogue = temp->data.content;
		dialogue[0] += std::to_string(temp->data.progress);
		dialogue[0] += '/';
		dialogue[0] += std::to_string(temp->data.number);
	}
	else {
		dialogue = temp->data.content;
	}
}