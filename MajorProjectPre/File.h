#pragma once

#include <iostream>

class File
{
#pragma region Constructors
public:
	File();

#pragma endregion
	   	 
#pragma region Methods

public:
	FILE* ErrorCheck(FILE* file, const char* filePath, const char* mode);

#pragma endregion

};

