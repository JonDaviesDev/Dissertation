#pragma once

#pragma region Includes

#include <array>
#include "BMPInfoHeader.h"

#pragma endregion

class BMPFileHeader
{
#pragma region Attributes

private:
	const short int fileHeaderSize;					// Size of the header

	short int fileSize;								// Size of the entire bmp file

	std::array<unsigned char, 13> fileHeader;

#pragma endregion

#pragma region Constructors

public:
	BMPFileHeader(BMPInfoHeader* infoHeader);

#pragma endregion

#pragma region Properties

public:
	short int GetSize();

#pragma endregion

#pragma region Methods

public:
	void CreateFileHeader(short int infoHeaderSize);

#pragma endregion
};

