#include "teleporter.h"

bool Teleporter::isTeleport(SDL_Point p) {
	SDL_Rect i = getRect();
	if (SDL_PointInRect(&p, &i)) {
		std::cout << "changing map" << std::endl;
		return true;
	}
	return false;
}

void Teleporter::render() {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &desRect);
}

void Teleporter::init() {
	desRect.w = 100;
	desRect.h = 100;
	setLocation({ 300, 300 });
}

void Teleporter::setMap(Map map) {
	this->map = map;
}

void Teleporter::setDestination(Map destination) {
	this->destination = destination;
}

void Teleporter::setColliderPath(std::string path) {
	this->colliderPath = path;
}

void Teleporter::setInterfacePath(std::string path) {
	this->interfacePath = path;
}

void Teleporter::setDestinationPoint(SDL_Point destination) {
	this->location = destination;
}

Map Teleporter::getCurrentMap() {
	return map;
}

Map Teleporter::getDestination() {
	return destination;
}

std::string Teleporter::getColliderPath() {
	return colliderPath;
}

std::string Teleporter::getInterfacePath() {
	return interfacePath;
}

SDL_Point Teleporter::getDestinationPoint() {
	return location;
}