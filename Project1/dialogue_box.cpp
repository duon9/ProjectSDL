#include "dialogue_box.h"

void DialogueBox::show() {
	if (isShow) next();
	else {
		global::isPause = true;
		isShow = true;
		present();
	}
}

void DialogueBox::hide() {
	isShow = false;
}

void DialogueBox::render() {
	//if (isShow) TextureManagement::FillRect(global::renderer, { 0,255,0,255 }, { BOX_X, BOX_Y, BOX_WIDTH, BOX_HEIGHT });
	if (isShow) {
		SDL_RenderCopy(global::renderer, texture, NULL, &des);
		lbmp.show(texture, current);
	}
}

void DialogueBox::next() {
	if (current == next_content) {
		global::isPause = false;
		resetContent();
		clear();
		hide();
		//global::isPause = false;
		return;
	}
	clear();
	current = next_content;
}

void DialogueBox::setBackground() {
	SDL_SetRenderTarget(global::renderer, texture);

	SDL_SetRenderDrawColor(global::renderer, 0, 255, 0, 0);
	SDL_RenderClear(global::renderer);

	SDL_SetRenderTarget(global::renderer, NULL);
}

void DialogueBox::present() {
	//lbmp.show(texture);
}

void DialogueBox::clear() {
	//setBackground();
	SDL_SetRenderTarget(global::renderer, texture);
	SDL_RenderClear(global::renderer);
	SDL_SetRenderTarget(global::renderer, NULL);
	lbmp.setCurr();
}

void DialogueBox::resetContent() {
	current = content;
}