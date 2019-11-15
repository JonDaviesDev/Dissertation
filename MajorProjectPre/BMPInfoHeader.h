#pragma once

#pragma region Includes

#include <array>

#pragma endregion

class BMPInfoHeader
{
#pragma region Attributes

private:
	const int bytesPerPixel;

	int height, width, paddingSize;

	std::array<unsigned char, 40> infoHeader;

#pragma endregion

#pragma region Constructors

public:
	BMPInfoHeader();

#pragma endregion

#pragma region Properties

public:
	int GetSize();

	int GetBytesPerPixel();

	void SetHeight(int value);

	int GetHeight();

	void SetWidth(int value);

	int GetWidth();

	int GetPaddingSize();

#pragma endregion

#pragma region Methods

public:
	void CreateInfoHeader();



#pragma endregion
};

