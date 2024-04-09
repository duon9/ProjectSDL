#pragma once
#include "entity.h"
#include "sfx.h"

class Animated : public Entity
{
public:
	Animated(SDL_Renderer* renderer) : Entity(renderer) {
		//SDL_Log("Animated constructor called \n");
	}
	~Animated() {
		SDL_Log("Animated destructor called \n");
	}

	virtual void setClip(); // -> Animated
	virtual void setFrameLimit(); //-> Animated
	virtual void setLumination();
	//void setSFX(); //sound

protected:
	std::vector<Frame> frame; //-> Animated
	std::vector<std::vector<SDL_Rect>> wareClips; //-> Animated
	int frameCount; //-> Animated
	int frameTick; // -> Animated

};

