#include "tutorial.h"
#include "global.h"

void Tutorial::init() {
	object = { 20, 20, SCREEN_WIDTH - 40, SCREEN_HEIGHT - 40 };
	//fbutton = TTF_OpenFont("assets/fonts/test.ttf", 20);
	text1 = TextureManagement::LoadText(renderer, font, "SAVE");
	text2 = TextureManagement::LoadText(renderer, font, "SAVE", { 255,255,255,255 });
	fps60 = new AnimatedButton(renderer, { 200,40, 100,40 }, "60", font);
	fps90 = new AnimatedButton(renderer, { 350, 40, 100, 40 }, "90", font);
	fps60->init();
	fps90->init();
	fps = TextureManagement::LoadText(renderer, font, "FPS:");
	SDL_QueryTexture(fps, NULL, NULL, &fpsdes.w, &fpsdes.h);
	SDL_QueryTexture(text1, NULL, NULL, &button.w, &button.h);
	button.x = SCREEN_WIDTH - 20 - 20 - button.w;
	button.y = SCREEN_HEIGHT - 20 - 20 - button.h;
	texture = text1;
}

void Tutorial::render() {
	TextureManagement::FillRect(renderer, { 50,50,50, 150 }, object);
	fps60->render();
	fps90->render();
	SDL_RenderCopy(renderer, fps, NULL, &fpsdes);
	SDL_RenderCopy(renderer, texture, NULL, &button);
	//test();
}

bool Tutorial::handleEvents(SDL_Event e) {
	//SDL_Point curr = { e.motion.x, e.motion.y };

	if (fps60->handleUserMouseMotion(e)) {
		global::fps = 10;
	}
	if (fps90->handleUserMouseMotion(e)) {
		global::fps = 90;
	}

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