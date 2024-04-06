#pragma once
#include "global.h"

class PauseWindow
{
private:
	PauseWindow() {

	}

	PauseWindow(const PauseWindow&) = delete;
	void operator=(const PauseWindow&) = delete;

protected:

public:
	static PauseWindow& getInstance() {
		static PauseWindow instance;
		return instance;
	}

	void render();
};

