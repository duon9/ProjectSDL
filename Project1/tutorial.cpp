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
	test();
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

void Tutorial::test() {
	SDL_Vertex vertex_1 = { {10.5, 10.5}, {255, 0, 0, 255}, {1, 1} };
	SDL_Vertex vertex_2 = { {20.5, 10.5}, {255, 0, 0, 255}, {1, 1} };
	SDL_Vertex vertex_3 = { {10.5, 20.5}, {255, 0, 0, 255}, {1, 1} };

	// Put them into array

	SDL_Vertex vertices[] = {
		vertex_1,
		vertex_2,
		vertex_3
	};

	// Set renderer color

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	// Render red triangle

	SDL_RenderGeometry(renderer, texture, vertices, 3, NULL, 0);

}