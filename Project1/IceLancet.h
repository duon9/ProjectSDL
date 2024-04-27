#pragma once
#include "Missle.h"
#include "Ice.h"

class IceLancet : public Missle
{
private:
	static std::vector<std::vector<SDL_Rect>> clips;
	static std::vector<Frame> limits;
	static SDL_Texture* vessel;
	const static int damage = 100;
public:
	IceLancet(SDL_Renderer* renderer, SDL_Point currPos, SDL_Point desPos, SDL_Point camera, Uint32 code) : Missle(renderer, currPos, desPos, camera, code) {
		wareClips = &IceLancet::clips;
		frame = &IceLancet::limits;
		desRect.w = 72;
		desRect.h = 48;
	}

	~IceLancet() {

	}
	static void loadClips();
	static void loadTexture(SDL_Renderer* renderer);
	virtual void draw() override;
	virtual void handleEffect(SDL_Rect target) override;
};

