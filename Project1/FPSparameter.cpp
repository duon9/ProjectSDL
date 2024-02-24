#include "FPSparameter.h"

void FPSparameter::updateFPS() {
	text = FPScontroller::getFPS();
}