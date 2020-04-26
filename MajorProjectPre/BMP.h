#pragma once

#pragma region Preprocessor Directives

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
#include "FileLoader.h"
#include "PixelContainer.h"

#pragma endregion

#pragma endregion

class BMP
{
#pragma region Attributes

private:
	BMPInfoHeader infoHeader;

	BMPFileHeader fileHeader;

	FileLoader* fileObject;

	PixelContainer pixels;

#pragma endregion

#pragma region Constructors

public:

	BMP();

	BMP(FileLoader* reader);

#pragma endregion

#pragma region Properties

#pragma region Setters

	void SetPixelContainer(PixelContainer pixelList);

#pragma endregion

#pragma region Getters

	int GetHeight();

	int GetWidth();

	int GetColourSpace();

	FileLoader* GetFileObject();

	BMPInfoHeader* GetInfoHeader();

	BMPFileHeader* GetFileHeader();

	PixelContainer* GetPixelContainer();

#pragma endregion

#pragma endregion

#pragma region Methods

	void ScanBMP();

	void ReadPixels();

	// Covert from Windows' native BGR to RGB
	void ConvertBGRtoRGB(unsigned char* data, int iteration);

#pragma region Display Functions

	void PrintHeader();

	void PrintPixels();

	void ImageBitRepresentation();

#pragma endregion


#pragma endregion
};


