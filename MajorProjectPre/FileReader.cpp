#include "FileReader.h"

#pragma region Constructors

FileReader::FileReader(const char* fileName) : fileName(fileName)
{
	// Ensure that the file has opened correctly on object creation
	inputFile = ErrorCheck(inputFile, fileName, "r");
}

#pragma endregion

#pragma region Properties

// Return the address of the file
FILE* FileReader::GetFile() { return inputFile; }

const char* FileReader::GetFileName() { return fileName; }

#pragma endregion

#pragma region Methods

#pragma endregion