#pragma once
#include "entity.h"

#define PER_FRAME 1
#define MAX_FRAME 900
#define COUNT 30
#define HALFCOUNT 15
class EarthPlanet : public Entity
{
private:
	int frameCount = 0;
	std::vector<SDL_Rect> clips;
	std::vector<std::vector<SDL_Rect>> luff;
	SDL_Texture* texture1 = nullptr;
	SDL_Texture* texture2 = nullptr;
	SDL_Texture* texture3 = nullptr;
	SDL_Texture* texture4 = nullptr;
public:
	EarthPlanet(SDL_Renderer* renderer) : Entity(renderer) {

	}

	~EarthPlanet() {

	}
	void loadClips();
	void loadTexture();
	void init();
	virtual void render() override;
};

