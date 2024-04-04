#include "dialogue_box.h"

void DialogueBox::show() {
	isShow = true;
}

void DialogueBox::hide() {
	isShow = false;
}

void DialogueBox::render() {
	if (isShow) TextureManagement::FillRect(global::renderer, { 0,255,0,255 }, { BOX_X, BOX_Y, BOX_WIDTH, BOX_HEIGHT });
}