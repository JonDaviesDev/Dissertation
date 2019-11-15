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

#pragma endregion

#pragma region Properties

public:

	void SetRGB(RGB value);

	RGB GetRGB();

#pragma endregion
};

