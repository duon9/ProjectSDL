#include "minotaur.h"

#define MINOTAUR "minotaur"

SDL_Texture* Minotaur::vessel = nullptr;
Stat Minotaur::base;

void Minotaur::setTexture(std::string path, SDL_Renderer* renderer) {
	Minotaur::vessel = TextureManagement::LoadTexture(path, renderer);
}

void Minotaur::setBase() {
	File::getProperties(MINOTAUR, Minotaur::base);
}