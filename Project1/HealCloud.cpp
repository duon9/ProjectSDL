#include "HealCloud.h"

#include "global.h"

void HealCloud::handleEvents() {
	if (!check_death) {
		//stat.health -= 10;
		listen(global::e);
		incinerate();
	}
}

void HealCloud::incinerate() {
	if (frameCount % 30 == 1) {
		for (int i = 0; i < global::layers.size(); i++) {
			if (global::layers[i]->getProtocolCode() != ALLY_CODE) {
				continue;
			}
			SDL_Rect v = global::layers[i]->getRect();
			if (SDL_HasIntersection(getDamageRect(), &v)) {
				global::layers[i]->handleMissle(-stat.damage, NONE);
				//stat.health += 1000;
			}
			//global::layers[i]->handleMissle(stat.damage, HPDrain);
		}
	}

}

SDL_Rect* HealCloud::getDamageRect() {
	SDL_Rect* res = new SDL_Rect();
	res->x = position.x + desRect.w / 6;
	res->y = position.y + desRect.w / 3;
	res->w = (desRect.w * 2) / 3;
	res->h = (desRect.h * 2) / 3;
	return res;
}

void HealCloud::handleLogic() {
	if (!check_death) {
		if (stat.health <= 0) {
			status = ENDING;
			frameCount = 0;
			check_death = true;
			lumi->w = 0;
			lumi->h = 0;
		}
		else {
			lumi->x = desRect.x + desRect.w / 2 - lumi->w / 2;
			lumi->y = desRect.y + desRect.h / 2 - lumi->h / 2;
		}
	}
}

void HealCloud::setLumination() {
	lumi = new SDL_Rect();
	lumi->w = 360;
	lumi->h = 360;
	lumi->x = desRect.x + desRect.w / 2 - lumi->w / 2;
	lumi->y = desRect.y + desRect.h / 2 - lumi->h / 2;
	global::lighthouse.push_back(lumi);
}