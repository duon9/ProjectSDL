#include "aniamted_obj.h"
#include "global.h"

void Animated::setFrameLimit() {
	//File::getFrameLimit(type, frame);

	if (global::frames[type] == nullptr) {
		global::frames[type] = new std::vector<Frame>;
		File::getFrameLimit(type, global::frames[type]);
		frame = global::frames[type];
	}
	else {
		frame = global::frames[type];
	}
}

void Animated::setClip() {
	//wareClips = File::getClips(type);
	if (global::clips[type] == nullptr) {
		global::clips[type] = new std::vector<std::vector<SDL_Rect>>;
		*global::clips[type] = File::getClips(type);
		wareClips = global::clips[type];
	}
	else {
		wareClips = global::clips[type];
	}
}

void Animated::setLumination() {
	
}

