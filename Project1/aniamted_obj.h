#pragma once
#include "entity.h"
class Animated : public Entity
{
public:
	Animated(SDL_Renderer* renderer) : Entity(renderer) {
		SDL_Log("Animated constructor called \n");
	}
	~Animated() {
		SDL_Log("Animated destructor called \n");
	}

	virtual void setClip(); // -> Animated
	virtual void setFrameLimit(); //-> Animated

protected:
	std::vector<Frame> frame; //-> Animated
	std::vector<std::vector<SDL_Rect>> wareClips; //-> Animated
	int frameCount; //-> Animated
	int frameTick; // -> Animated

};

