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

private:
	//The font texture
	LTexture mFontTexture;

	//The individual characters in the surface
	SDL_Rect mChars[256];

	//Spacing Variables
	int mNewLine, mSpace;
};

