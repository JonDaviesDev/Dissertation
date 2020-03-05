#pragma once

#pragma region Includes

#include "cRGB.h"

#pragma endregion


class Pixel
{
#pragma region Attributes

private:
	cRGB colour;

#pragma endregion

#pragma region Constructors

public:
	Pixel();

	Pixel(cRGB value);

	Pixel(unsigned char* data, int iterator);

	Pixel(unsigned char* data, int posY, int posX);

#pragma endregion

#pragma region Properties

public:

	void SetRGB(unsigned char r, unsigned char g, unsigned char b);

	cRGB GetRGB();

#pragma endregion
};

