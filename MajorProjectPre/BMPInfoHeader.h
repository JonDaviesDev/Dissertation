#pragma once

#pragma region Includes

#include <array>

#pragma endregion

class BMPInfoHeader
{
#pragma region Attributes

private:
	const short int bytesPerPixel;

	short int height, width;

	std::array<unsigned char, 40> infoHeader;

#pragma endregion

#pragma region Constructors

public:
	BMPInfoHeader(short int height, short int width);

#pragma endregion

#pragma region Properties

public:
	short int GetSize();

	short int GetBytesPerPixel();

	short int GetHeight();

	short int GetWidth();

#pragma endregion

#pragma region Methods

public:
	void CreateInfoHeader();

#pragma endregion
};

