#include "pauseWindow.h"

void PauseWindow::render() {
	if (global::isPause && global::isEscape) TextureManagement::FillRect(global::renderer, { 255,255,255,10 }, { 200, 150, 400,300 });
}