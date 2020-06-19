#pragma once

#pragma region Includes

#pragma region System Files

#include <array>
#include <iostream>

#pragma endregion

#pragma region Project Files

#include "BMPInfoHeader.h"
#include "FileLoader.h"

#pragma endregion

#pragma endregion

class BMPFileHeader
{
#pragma region Attributes

private:
	int fileHeaderSize;					// Size of the header

	size_t fileSize;							// Size of the entire bmp file

	const char* fileName;

	FileLoader* reader;

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

	void SetFileHeaderElement(unsigned char value, int elementNumber);

	void SetFileName(const char* value);

	void SetFileSize(size_t value);

#pragma endregion

#pragma region Getters

	const char* GetFileName();

	int GetSize();

	size_t GetFileSize();

	std::array<unsigned char, 14> GetFileData();

	FileLoader* GetReader();

#pragma endregion
	
#pragma endregion

#pragma endregion

#pragma region Methods

public:
	void CreateFileHeader(BMPInfoHeader* info);

#pragma endregion
};

