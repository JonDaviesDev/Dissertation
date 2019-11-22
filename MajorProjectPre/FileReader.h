#pragma once

#pragma region Includes

#include <iostream>

#pragma endregion


class FileReader
{
#pragma region Attributes

private:
	FILE* inputFile;

	const char* fileName;

#pragma endregion

#pragma region Constructors

public:
	FileReader(const char* fileName);

#pragma endregion

#pragma region Properties

public:
	FILE* GetFile();

	const char* GetFileName();

#pragma endregion

#pragma region Methods

public:
	FILE* ErrorCheck(FILE* file, const char* filePath, const char* mode); // POSSIBLY CREATE A BASE CLASS FOR THE READER AND WRITER

#pragma endregion
};

