#pragma once

#pragma region Includes

#pragma region System Files

#include <array>

#pragma endregion

#pragma region Project Files

#include "FileReader.h"

#pragma endregion

#pragma endregion

class BMPInfoHeader
{
#pragma region Attributes

private:
	const int bytesPerPixel;

	int height, width, paddingSize;

	FileReader* reader;

	std::array<unsigned char, 40> infoHeader;

#pragma endregion

#pragma region Constructors

public:
	BMPInfoHeader(FileReader* reader);

#pragma endregion

#pragma region Properties

public:

#pragma region Setters

	void SetInfoHeader();

	void SetHeight(int value);

	void SetWidth(int value);

#pragma endregion

#pragma region Getters

	int GetSize();

	int GetBytesPerPixel();

	int GetHeight();

	int GetWidth();

	int GetPaddingSize();

#pragma endregion

#pragma endregion

#pragma region Methods

public:
	void CreateInfoHeader();

#pragma endregion
};

