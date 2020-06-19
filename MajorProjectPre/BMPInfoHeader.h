#pragma once

#pragma region Includes

#pragma region System Files

#include <array>

#pragma endregion

#pragma region Project Files

#include "FileLoader.h"

#pragma endregion

#pragma endregion

class BMPInfoHeader
{
#pragma region Attributes

private:
	const int bytesPerPixel;

	int height, width, paddingSize;

	FileLoader* reader;

	std::array<unsigned char, 40> infoHeader;

#pragma endregion

#pragma region Constructors

public:
	BMPInfoHeader(FileLoader* reader);

	BMPInfoHeader(int height, int width, int paddingSize);

#pragma endregion

#pragma region Properties

public:

#pragma region Setters

	void SetInfoHeader();

	void SetHeight(int value);

	void SetWidth(int value);

	void SetPaddingSize(int value);

#pragma endregion

#pragma region Getters

	int GetSize();

	int GetBytesPerPixel();

	int GetHeight();

	int GetWidth();

	int GetPaddingSize();

	FileLoader* GetReader();

	std::array<unsigned char, 40> GetInfoData();

#pragma endregion

#pragma endregion

#pragma region Methods

public:
	void CreateInfoHeader();

	void CalculatePaddingSize();

#pragma endregion
};

