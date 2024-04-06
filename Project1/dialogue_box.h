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
	LBitmapFont lbmp;
	std::string content = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
	std::string next_content = "fuck you bitch, get out of my tavern";
	std::string current;
	std::vector<std::string> contents;
	SDL_Texture* texture = SDL_CreateTexture(global::renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, BOX_WIDTH, BOX_HEIGHT);
	bool isShow = false;
	DialogueBox() {
		setBackground();
		lbmp.buildFont("assets/dialogue/lazyfont.png");
		lbmp.setLocation({ 0, 0});
		current = content;
	}

	DialogueBox(const DialogueBox&) = delete;
	void operator=(const DialogueBox&) = delete;

	SDL_Rect des = { BOX_X, BOX_Y, BOX_WIDTH, BOX_HEIGHT };
	SDL_Rect src;
	
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
	void present();
	void clear();
	void resetContent();
	void setBackground();
};

