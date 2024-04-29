#include "wizard.h"
#include "math.h"
#include "collision.h"

void Wizard::chaseTarget(Player* target) {
	if (!check_death && !global::isPause) {
		if (trackNearestTarget(target)) {
			if (!moveTo(target->getPosition())) {

				if (frameTick > 0) {
					frameTick--;
					return;
				}
				else {
					int x = Math::Casuale::casuale(1, 100);
					if (x == 1) {
						frameCount = 0;
						status = SPELLCAST;
						frameTick = frame->at(status).maxFrame;
						Ice* ice1 = new Ice(global::renderer);
						ice1->setLocation(target->getPosition());
						ice1->create();
						global::dtiles.push_back(ice1);
						global::layers.push_back(ice1);
						Fire* fire = new Fire(global::renderer);
						fire->setLocation(target->getPosition());
						fire->setLumination();
						global::dtiles.push_back(fire);
						global::layers.push_back(fire);
					}
					else if (x == 2) {
						frameCount = 0;
						status = ATTACKING;
						frameTick = (*frame)[status].maxFrame;
						//attack();
						LightingEagle* bomb = new LightingEagle(renderer, getPosition(), target->getPosition(), { 0,0 }, code);
						bomb->setSize(100, 100);
						global::missles.push_back(bomb);
					}
					else if (x == 3) {
						setLocation(target->getPosition());
					}
					else if (x == 4) {
						//setLocation({ Math::Casuale::casuale(100, Collision::getWidth() * 32), Math::Casuale::casuale(100, Collision::getHeight() * 32) });
					}
				}
				
			}
		}
		else {
			//stat.health += 100;
			status = IDLE;
		}
	}
}