#include "npc.h"

void NPC::listen(SDL_Event* e) {
	if (!check_pause) {
		SDL_Point point;

		if (protocol->receive(e, point)) {

			Math::Vector v = Math::Vector(getPosition(), point);
			if (v.getDistance() < 32 * 2) {
				std::cout << "found interact" << std::endl;
				box.show();
			}
		}
	}
}