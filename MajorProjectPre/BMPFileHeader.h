#pragma once

#pragma region Includes

#include <array>
#include <iostream>
#include "BMPInfoHeader.h"

#pragma endregion

class BMPFileHeader
{
#pragma region Attributes

private:
	const int fileHeaderSize;					// Size of the header

	int fileSize;								// Size of the entire bmp file

	std::string fileName;

	std::array<unsigned char, 14> fileHeader;

#pragma endregion

#pragma region Constructors

public:
	BMPFileHeader(BMPInfoHeader* infoHeader);

#pragma endregion

#pragma region Properties

public:
	void SetHeader(char* headerInfo, std::string filePath, std::ifstream* inputFile);

	int GetSize();

#pragma endregion

#pragma region Methods

public:
	void CreateFileHeader(int infoHeaderSize);

#pragma endregion
};

