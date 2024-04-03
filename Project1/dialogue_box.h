#pragma once
#include <SDL.h>
#include <vector>
#include <iostream>

class DialogueBox
{
private:
	SDL_Renderer* renderer = nullptr;
	SDL_Rect src;
	SDL_Rect des;
	std::vector<std::string> dialogue;
	bool isShow = false;
	int currDialogue = 0;
public:
	DialogueBox(SDL_Renderer* renderer) {
		this->renderer = renderer;
	}

	~DialogueBox() {

	}

	void add(std::string content);
	void show();
	void next();

};

