#pragma once

#pragma region Includes

#pragma region System Files

#include <vector>

#pragma endregion

#pragma region Project Files

#include "Pixel.h"
#include "BMP.h"
#include "BMPInfoHeader.h"
#include "BMPFileHeader.h"
#include "PixelContainer.h"

#pragma endregion

#pragma endregion

class BMPWriter
{
#pragma region Attributes

private:
	const char* fileName;

	FILE* fileObject;

	int height, width, colourSpace;

	BMP* bmp;

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
	void CreateNewBMP(const char* fileName, int width, int height, RGB colour);

	void CloneBMP(BMP* bmp);

	void GenerateImageData(PixelContainer image, int height, int width, const char* imageFileName);

	unsigned char* CreateFileHeader(int height, int width, int paddingSize);

	unsigned char* CreateInfoHeader(int height, int width);

	FILE* ErrorCheck(FILE* file, const char* filePath, const char* mode);

#pragma endregion
};

