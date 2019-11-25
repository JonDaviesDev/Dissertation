#pragma once

#pragma region Preprocessor Directives

#pragma region Includes

#include <iostream>
#include "File.h"

#pragma endregion

#pragma endregion

class FileReader : public File
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
	
#pragma endregion
};

