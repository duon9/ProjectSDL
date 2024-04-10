#pragma once
#include "teleporter.h"
#include "global.h"
class Portal : public Teleporter
{
private:
	
	int frameCount = 0;
	static SDL_Texture* vessel;
	static std::vector<SDL_Rect> clips;
public:

	Portal() : Teleporter(global::renderer) {
	}

	~Portal() {

	}

	static void loadTexture(); 
	static void loadClip();
	virtual void render() override;
	virtual void init() override;
};

