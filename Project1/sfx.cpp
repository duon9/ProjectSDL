#include "sfx.h"

SFX::SFX() {

}

SFX::~SFX() {
	Mix_FreeChunk(sound);
}

void SFX::init() {
	/*if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) return false;
	return true;*/
}

void SFX::play() {
	Mix_PlayChannel(-1, sound, -1);
}

bool SFX::add(std::string path) {
	sound = Mix_LoadWAV(path.c_str());
	if (sound != nullptr) return true;
	return false;
}

void SFX::stop() {
	Mix_HaltChannel(-1);
}