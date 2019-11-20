#include "BMPWriter.h"


#pragma region Constructors

BMPWriter::BMPWriter() 
	: height(500), width(500), colourSpace(3), bmp(nullptr) 
{
	image = {PixelVector2D(height, PixelVector1D(width, Pixel(RGB())))};
}

BMPWriter::BMPWriter(BMP* bmp) 
	: height(bmp->GetHeight()), width(bmp->GetWidth()), colourSpace(bmp->GetColourSpace()), bmp(bmp) 
{
	image = {PixelVector2D(height, PixelVector1D(width, Pixel(RGB())))};
}

#pragma endregion

#pragma region Properties

#pragma region Setters

void BMPWriter::SetHeight(int value) { height = value; }

void BMPWriter::SetWidth(int value) { width = value; }

void BMPWriter::SetColourSpace(int value) { colourSpace = value; }

#pragma endregion

#pragma region Getters

int BMPWriter::GetHeight() { return height; }

int BMPWriter::GetWidth() { return width; }

int BMPWriter::GetColourSpace() { return colourSpace; }

#pragma endregion

#pragma endregion

#pragma region Methods

void BMPWriter::CreateNewBMP()
{
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			image[i][j].SetRGB(255, 0, 0);
		}
	}


}

#pragma endregion
