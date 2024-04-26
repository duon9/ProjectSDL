#include "Ice.h"
#include "collision.h"
void Ice::create() {
	Collision::update({ position.x + desRect.w / 2,position.y + desRect.y });
}