#include "Pixel.h"

#pragma region Constructors

Pixel::Pixel() : colour(0, 0, 0) {}

Pixel::Pixel(RGB value) : colour(value) {}

Pixel::Pixel(unsigned char* data, int iterator) : colour(data[iterator], data[iterator + 1], data[iterator + 2]) {}

Pixel::Pixel(unsigned char* data, int posY, int posX) : colour(data[posX], data[posX + 1], data[posX + 2]){}

#pragma endregion

#pragma region Properties

void Pixel::SetRGB(unsigned char r, unsigned char g, unsigned char b) { colour.SetRed(r), colour.SetGreen(g), colour.SetBlue(b); }

RGB Pixel::GetRGB() { return colour; }

#pragma endregion

