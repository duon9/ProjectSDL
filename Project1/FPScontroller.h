#pragma once
#include <SDL.h>
#include <iomanip>


class FPScontroller
{
public:
	static void FPSlimit(int framerate);
	static float getFPS();
};

