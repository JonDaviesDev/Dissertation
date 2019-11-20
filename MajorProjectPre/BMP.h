#pragma once

#pragma region Includes

#pragma region System Files

#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <sstream>

#pragma endregion

#pragma region Project Files

#include "Pixel.h"
#include "BMPFileHeader.h"
#include "BMPInfoHeader.h"
#include "FileReader.h"

#pragma endregion

#pragma endregion

class BMP
{
#pragma region Attributes

private:
	BMPInfoHeader infoHeader;

	BMPFileHeader fileHeader;

	FileReader* fileObject;

	std::vector<std::vector<Pixel>> pixelsData;

#pragma endregion

#pragma region Constructors

public:

	BMP();

	BMP(FileReader* reader);

#pragma endregion

#pragma region Properties

#pragma region Setters

#pragma endregion

#pragma region Getters

	int GetHeight();

	int GetWidth();

	int GetColourSpace();

#pragma endregion

#pragma endregion

#pragma region Methods

	void ScanBMP();

	void ReadPixels();

	void ConvertBGRtoRGB(unsigned char* data, int iteration);

#pragma region Display Functions

	void PrintHeader();

#pragma endregion


#pragma endregion
};


