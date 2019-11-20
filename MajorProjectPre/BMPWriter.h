#pragma once

#pragma region Includes

#pragma region System Files

#include <vector>

#pragma endregion

#pragma region Project Files

#include "Pixel.h"
#include "BMP.h"

#pragma endregion



#pragma endregion

using PixelVector2D = std::vector<std::vector<Pixel>>;
using PixelVector1D = std::vector<Pixel>;

class BMPWriter
{
#pragma region Attributes

private:
	int height;

	int width;

	int colourSpace;

	BMP* bmp;

	std::vector<std::vector<Pixel>> image;

#pragma endregion

#pragma region Constructors

public:
	BMPWriter();

	BMPWriter(BMP* bmp);

#pragma endregion

#pragma region Properties

public:
#pragma region Setters

	void SetHeight(int value);

	void SetWidth(int value);

	void SetColourSpace(int value);

#pragma endregion

#pragma region Getters

	int GetHeight();

	int GetWidth();

	int GetColourSpace();

#pragma endregion

#pragma endregion

#pragma region Methods

public:
	void CreateNewBMP();

	void GenerateImageData();

#pragma endregion
};

