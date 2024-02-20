//#include "TestObject.h"
//void TestObject::handleUserEvents(SDL_Event e) {
//	if (!check_death && !check_pause) {
//		if (isAction) {
//			action();
//			return;
//		}
//		else if (!isAction && (check_run || check_attack)) {
//			if (check_attack) {
//				if (e.type == SDL_KEYUP && e.type == SDLK_z) {
//					check_attack = false;
//					status = IDLE;
//
//				}
//				else if (e.type == SDL_KEYDOWN && e.type == SDLK_z) {
//					check_attack = true;
//					check_run = false;
//					isAction = true;
//					status = ATTACKING;
//				}
//			}
//		}
//	}
//}