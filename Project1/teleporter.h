#pragma once
#include "entity.h"

class Teleporter : public Entity
{
private:
	Map map;
	Map destination;
	std::string colliderPath;
	std::string interfacePath;
	SDL_Point location;

public:
	Teleporter(SDL_Renderer* renderer) : Entity(renderer) {

	}
	
	~Teleporter() {

	}
	virtual void init() override;
	virtual void render() override;
	bool isTeleport(SDL_Point p);
	void setMap(Map map);
	void setDestination(Map destination);
	void setColliderPath(std::string path);
	void setInterfacePath(std::string path);
	void setDestinationPoint(SDL_Point destination);
	Map getCurrentMap();
	Map getDestination();
	std::string getColliderPath();
	std::string getInterfacePath();
	SDL_Point getDestinationPoint();

};

