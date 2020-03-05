#pragma once
#include "File.h"

class FileLoader
{
#pragma region Attributes

private:
	File file;

#pragma endregion

#pragma region Constructors

public:
	FileLoader();

	FileLoader(const char* fileName);

	FileLoader(FILE* file);

#pragma endregion

#pragma region Properties

	void SetName(const char* value);

	FILE* GetFile();

	const char* GetFileName();

#pragma endregion


#pragma region Methods

public:
	FILE* ErrorCheck(FILE* file, const char* filePath, const char* mode);

#pragma endregion
};

