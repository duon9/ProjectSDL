#pragma once
#include "LTexture.h"

class LBitmapFont
{
public:
	//The default constructor
	LBitmapFont();

	//Generates the font
	bool buildFont(std::string path);

	//Deallocates font
	void free();

	//Shows the text
	void renderText(int x, int y, std::string text);

	void show();
	void present();
	void setCurr();

private:
	int curr = 0;
	int curX = 0;
	int curY = 0;
	SDL_Texture* target = SDL_CreateTexture(global::renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, 800, 200);
	std::string content = "Hello frome heaven, you look so cute, I am the grand chancellor of \n the republic";
	//The font texture
	LTexture mFontTexture;

	//The individual characters in the surface
	SDL_Rect mChars[256];

	//Spacing Variables
	int mNewLine, mSpace;
};

