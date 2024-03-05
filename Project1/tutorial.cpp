#include "tutorial.h"

void Tutorial::init() {
	object = { 20, 20, SCREEN_WIDTH - 40, SCREEN_HEIGHT - 40 };
	text1 = TextureManagement::LoadText(renderer, font, "UNDERSTAND");
	text2 = TextureManagement::LoadText(renderer, font, "UNDERSTAND", { 255,255,255,255 });
	SDL_QueryTexture(text1, NULL, NULL, &button.w, &button.h);
	button.x = SCREEN_WIDTH - 20 - 20 - button.w;
	button.y = SCREEN_HEIGHT - 20 - 20 - button.h;
	texture = text1;
}

void Tutorial::render() {
	TextureManagement::FillRect(renderer, { 50,50,50, 150 }, object);
	SDL_RenderCopy(renderer, texture, NULL, &button);
}

bool Tutorial::handleEvents(SDL_Event e) {
	//SDL_Point curr = { e.motion.x, e.motion.y };
	if (e.type == SDL_MOUSEMOTION) {
		SDL_Point curr = { e.motion.x, e.motion.y };
		if (SDL_PointInRect(&curr, &button)) {
			texture = text2;
		}
		else {
			texture = text1;
		}
	}
	else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
		SDL_Point curr = { e.motion.x, e.motion.y };
		if (SDL_PointInRect(&curr, &button)) {
			return 1;
		}
	}
	return false;
}