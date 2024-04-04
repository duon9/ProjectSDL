#pragma once
#include <SDL.h>
#include <vector>
#include <iostream>
#include "LBitmapFont.h"
//#include "protocol.h"

#define BOX_X 50
#define BOX_Y 0
#define BOX_WIDTH 600
#define BOX_HEIGHT 100

class DialogueBox
{
private:
	std::vector<std::string> contents;
	bool isShow = false;
	DialogueBox() {

	}

	DialogueBox(const DialogueBox&) = delete;
	void operator=(const DialogueBox&) = delete;
	
public:
	static DialogueBox& getInstance() {
		static DialogueBox instance;
		return instance;
	}

	void updateContent(std::vector<std::string> contents);
	void show();
	void hide();
	void next();
	void render();
};

