#pragma once

#pragma region Includes

#include "RGB.h"

#pragma endregion


class Pixel
{
#pragma region Attributes

private:
	RGB colour;

#pragma endregion

#pragma region Constructors

public:
	Pixel();

	Pixel(RGB value);

	Pixel(unsigned char* data, int iterator);

	Pixel(unsigned char* data, int posY, int posX);

#pragma endregion

#pragma region Properties

public:

	void SetRGB(unsigned char r, unsigned char g, unsigned char b);

	RGB GetRGB();

#pragma endregion
};

