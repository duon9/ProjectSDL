#include "guidegirl.h"
#include <iostream>
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
	/*std::cout << temp.data.content.size() << std::endl;
	std::cout << temp.data.name << std::endl;
	std::cout << temp.data.object << std::endl;
	std::cout << temp.data.number << std::endl;*/

	dialogue = temp.content;
	dialogue[dialogue.size() - 1] += std::to_string(temp.progress);
	dialogue[dialogue.size() - 1] += '/';
	dialogue[dialogue.size() - 1] += std::to_string(temp.number);
}