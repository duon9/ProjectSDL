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
	global::isPause = false;
	isShow = false;
}

void DialogueBox::render() {
	//if (isShow) TextureManagement::FillRect(global::renderer, { 0,255,0,255 }, { BOX_X, BOX_Y, BOX_WIDTH, BOX_HEIGHT });
	if (isShow) {
		SDL_RenderCopy(global::renderer, texture, NULL, &des);
		lbmp.show(texture, contents[content]);
	}
}

void DialogueBox::next() {
	if (content == contents.size() - 1) {
		global::isPause = false;
		resetContent();
		clear();
		hide();
		//global::isPause = false;
		return;
	}
	clear();
	content++;
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
	content = 0;
}

void DialogueBox::addDialogue(std::vector<std::string> contents) {
	this->contents = contents;
}