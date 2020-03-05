#pragma once

#include <iostream>

class File
{
#pragma region Attributes

private:
	FILE* file;

	const char* fileName;

#pragma endregion
	
#pragma region Constructors
public:
	File();

	File(const char* fileName);

#pragma endregion

#pragma region Properties

	void SetName(const char* value);

	void SetFile(FILE* file);

	FILE* GetFile();

	const char* GetName();

#pragma endregion

};

