#pragma once

#pragma region Includes

#pragma region System Files

#include <array>
#include <iostream>

#pragma endregion

#pragma region Project Files

#include "BMPInfoHeader.h"
#include "FileReader.h"

#pragma endregion

#pragma endregion

class BMPFileHeader
{
#pragma region Attributes

private:
	const int fileHeaderSize;					// Size of the header

	size_t fileSize;							// Size of the entire bmp file

	std::string fileName;

	FileReader* reader;

	std::array<unsigned char, 14> fileHeader;

#pragma endregion

#pragma region Constructors

public:
	BMPFileHeader(BMPInfoHeader* infoHeader);

#pragma endregion

#pragma region Properties

public:

#pragma region Setters

	void SetFileHeader(BMPInfoHeader* info);

	void SetFileName(std::string value);

	void SetFileSize(size_t value);

#pragma endregion

#pragma region Getters

	int GetSize();

	size_t GetFileSize();

#pragma endregion
	
#pragma endregion

#pragma endregion

#pragma region Methods

public:
	void CreateFileHeader(BMPInfoHeader* info);

#pragma endregion
};

