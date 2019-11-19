#include "Pixel.h"

#pragma region Constructors

Pixel::Pixel() : colour(0, 0, 0) {}

Pixel::Pixel(RGB value) : colour(value) {}

Pixel::Pixel(unsigned char* data, int iterator) : colour(data[iterator], data[iterator + 1], data[iterator + 2]) {}

#pragma endregion

#pragma region Properties

void Pixel::SetRGB(unsigned char r, unsigned char g, unsigned char b) { colour.SetRed(r), colour.SetGreen(g), colour.SetBlue(b); }

void Pixel::SetRGB(unsigned char* data, int iterator)
{
	colour.SetRed(data[iterator]);

	colour.SetGreen(data[iterator + 1]);

	colour.SetBlue(data[iterator + 2]);
}

RGB Pixel::GetRGB() { return colour; }

#pragma endregion

