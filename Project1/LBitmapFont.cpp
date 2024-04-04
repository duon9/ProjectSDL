#include "LBitmapFont.h"

LBitmapFont::LBitmapFont()
{
	//Initialize variables
	mNewLine = 0;
	mSpace = 0;
}

bool LBitmapFont::buildFont(std::string path)
{
	//Get rid of preexisting texture
	free();

	//Load bitmap image
	bool success = true;
	if (!mFontTexture.loadPixelsFromFile(path))
	{
		printf("Unable to load bitmap font surface!\n");
		success = false;
	}
	else
	{
		//Get the background color
		Uint32 bgColor = mFontTexture.getPixel32(0, 0);

		//Set the cell dimensions
		int cellW = mFontTexture.getWidth() / 16;
		int cellH = mFontTexture.getHeight() / 16;

		//New line variables
		int top = cellH;
		int baseA = cellH;

		//The current character we're setting
		int currentChar = 0;

		//Go through the cell rows
		for (int rows = 0; rows < 16; ++rows)
		{
			//Go through the cell columns
			for (int cols = 0; cols < 16; ++cols)
			{
				//Set the character offset
				mChars[currentChar].x = cellW * cols;
				mChars[currentChar].y = cellH * rows;

				//Set the dimensions of the character
				mChars[currentChar].w = cellW;
				mChars[currentChar].h = cellH;

				//Find Left Side
				//Go through pixel columns
				for (int pCol = 0; pCol < cellW; ++pCol)
				{
					//Go through pixel rows
					for (int pRow = 0; pRow < cellH; ++pRow)
					{
						//Get the pixel offsets
						int pX = (cellW * cols) + pCol;
						int pY = (cellH * rows) + pRow;

						//If a non colorkey pixel is found
						if (mFontTexture.getPixel32(pX, pY) != bgColor)
						{
							//Set the x offset
							mChars[currentChar].x = pX;

							//Break the loops
							pCol = cellW;
							pRow = cellH;
						}
					}
				}

				//Find Right Side
				//Go through pixel columns
				for (int pColW = cellW - 1; pColW >= 0; --pColW)
				{
					//Go through pixel rows
					for (int pRowW = 0; pRowW < cellH; ++pRowW)
					{
						//Get the pixel offsets
						int pX = (cellW * cols) + pColW;
						int pY = (cellH * rows) + pRowW;

						//If a non colorkey pixel is found
						if (mFontTexture.getPixel32(pX, pY) != bgColor)
						{
							//Set the width
							mChars[currentChar].w = (pX - mChars[currentChar].x) + 1;

							//Break the loops
							pColW = -1;
							pRowW = cellH;
						}
					}
				}

				//Find Top
				//Go through pixel rows
				for (int pRow = 0; pRow < cellH; ++pRow)
				{
					//Go through pixel columns
					for (int pCol = 0; pCol < cellW; ++pCol)
					{
						//Get the pixel offsets
						int pX = (cellW * cols) + pCol;
						int pY = (cellH * rows) + pRow;

						//If a non colorkey pixel is found
						if (mFontTexture.getPixel32(pX, pY) != bgColor)
						{
							//If new top is found
							if (pRow < top)
							{
								top = pRow;
							}

							//Break the loops
							pCol = cellW;
							pRow = cellH;
						}
					}
				}

				//Find Bottom of A
				if (currentChar == 'A')
				{
					//Go through pixel rows
					for (int pRow = cellH - 1; pRow >= 0; --pRow)
					{
						//Go through pixel columns
						for (int pCol = 0; pCol < cellW; ++pCol)
						{
							//Get the pixel offsets
							int pX = (cellW * cols) + pCol;
							int pY = (cellH * rows) + pRow;

							//If a non colorkey pixel is found
							if (mFontTexture.getPixel32(pX, pY) != bgColor)
							{
								//Bottom of a is found
								baseA = pRow;

								//Break the loops
								pCol = cellW;
								pRow = -1;
							}
						}
					}
				}

				//Go to the next character
				++currentChar;
			}
		}

		//Calculate space
		mSpace = cellW / 2;

		//Calculate new line
		mNewLine = baseA - top;

		//Lop off excess top pixels
		for (int i = 0; i < 256; ++i)
		{
			mChars[i].y += top;
			mChars[i].h -= top;
		}

		//Create final texture
		if (!mFontTexture.loadFromPixels())
		{
			printf("Unable to create font texture!\n");
			success = false;
		}
	}

	return success;
}

void LBitmapFont::free()
{
	mFontTexture.free();
}

void LBitmapFont::renderText(int x, int y, std::string text)
{
	//If the font has been built
	if (mFontTexture.getWidth() > 0)
	{
		//Temp offsets
		int curX = x, curY = y;

		//Go through the text
		for (int i = 0; i < text.length(); ++i)
		{
			//If the current character is a space
			if (text[i] == ' ')
			{
				//Move over
				curX += mSpace;
			}
			//If the current character is a newline
			else if (text[i] == '\n')
			{
				//Move down
				curY += mNewLine;

				//Move back
				curX = x;
			}
			else
			{
				//Get the ASCII value of the character
				int ascii = (unsigned char)text[i];

				//Show the character
				mFontTexture.render(curX, curY, &mChars[ascii]);

				//Move over the width of the character with one pixel of padding
				curX += mChars[ascii].w + 1;
			}
		}
	}
}

void LBitmapFont::show() {

	if (curr == content.size()) return;
	SDL_SetRenderTarget(global::renderer, target);
	if (curr == 0) TextureManagement::FillRect(global::renderer, { 0,255, 0, 255 }, { 0,0,800,200 });
	if (mFontTexture.getWidth() > 0)
	{
		//Temp offsets
		//curX = 0, curY = 0;

		if (content[curr] == ' ')
		{
			curX += mSpace;
		}
		else if (content[curr] == '\n')
		{
			curY += mNewLine;
			curX = 0;
		}
		else
		{
			int ascii = (unsigned char)content[curr];

			mFontTexture.render(curX, curY, &mChars[ascii]);

			curX += mChars[ascii].w + 1;
		}
	}

	SDL_SetRenderTarget(global::renderer, NULL);
	curr++;
}

void LBitmapFont::present() {
	SDL_Rect des = { 0,0, 800, 200 };
	SDL_SetRenderDrawColor(global::renderer, 0, 255, 255, 255);
	SDL_RenderCopy(global::renderer, target, NULL, &des);
}

void LBitmapFont::setCurr() {
	curr = 0;
	curX = 0;
	curY = 0;
}