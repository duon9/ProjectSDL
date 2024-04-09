#include "aniamted_obj.h"

void Animated::setFrameLimit() {
	File::getFrameLimit(type, frame);
}

void Animated::setClip() {
	wareClips = File::getClips(type);
}

void Animated::setLumination() {

}