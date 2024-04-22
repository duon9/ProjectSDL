#include "npc.h"

void NPC::listen(SDL_Event* e) {
	if (!check_pause) {
		SDL_Point point;
		bool query;
		if (protocol->receive(e, point, query)) {
			Math::Vector v = Math::Vector(getPosition(), point);
			if (v.getDistance() < 32 * 2) {
				if (box.box_target == type) {

				}
				else {
					box.addDialogue(dialogue);
					box.box_target = type;
				}
				if (query) {
					box.show();
					//global::isPause = true;
				}
				else {
					box.hide();
					box.resetContent();
					box.clear();
					//global::isPause = false;
				}
			}
		}
	}
}

void NPC::update() {

}