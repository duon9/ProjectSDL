#include "animated_button.h"

void AnimatedButton::handleUserMouseMotion(SDL_Event& e) {
	//SDL_Point currMousePosition = { e.motion.x, e.motion.y };
	if (e.type == SDL_MOUSEMOTION) {
		SDL_Point currMousePosition = { e.motion.x, e.motion.y };

		if (SDL_PointInRect(&currMousePosition, &outerRect) == true) {
			//std::cout << "found" << std::endl;
			color1 = { 0,0,0,255 };
			text = TextureManagement::LoadText(renderer, font, content, { 255,0,0,255 });
		}
		else {
			color1 = { 255,255,255,255 };
			text = TextureManagement::LoadText(renderer, font, content, { 0,0,0,255 });

		}
	}
}

void AnimatedButton::init() {
	text = TextureManagement::LoadText(renderer, font, content, {0,0,0,255});
	//text2 = TextureManagement::LoadText(renderer, font, content, { 255,255,255,255 });
	TextureManagement::loadTextRect(text, textRect, outerRect);
}

void AnimatedButton::render() {
	//TextureManagement::DrawRect(renderer, {0,0,0,255}, outerRect);
	TextureManagement::FillRect(renderer, {255,255,255,255}, outerRect);
	TextureManagement::DrawRect(renderer, { 0, 0, 0, 255 }, innerRect);
	TextureManagement::FillRect(renderer, color1, interRect);
	SDL_RenderCopy(renderer, text, NULL, &textRect);
}