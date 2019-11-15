#include "Pixel.h"

#pragma region Constructors

Pixel::Pixel() : colour(0, 0, 0) {}

Pixel::Pixel(RGB value) : colour(value) {}

#pragma endregion

#pragma region Properties

void Pixel::SetRGB(RGB value) { colour = value; }

RGB Pixel::GetRGB() { return colour; }

#pragma endregion

