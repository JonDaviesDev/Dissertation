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

#pragma endregion

#pragma region Properties

public:

	void SetRGB(unsigned char r, unsigned char g, unsigned char b);

	void SetRGB(unsigned char* data, int iterator);

	RGB GetRGB();

#pragma endregion
};

