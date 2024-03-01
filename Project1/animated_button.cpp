#include "animated_button.h"

void AnimatedButton::handleUserMouseMotion(SDL_Event& e) {
	SDL_Point currMousePosition = { e.motion.x, e.motion.y };
	if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
		Global::gamestate = PLAY;
	}
}

void AnimatedButton::init() {
	text = TextureManagement::LoadText(renderer, font, content);
	TextureManagement::loadTextRect(text, textRect, outerRect);

}