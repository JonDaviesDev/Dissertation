#include "FileReader.h"

#pragma region Constructors

FileReader::FileReader(std::string fileName) : fileName(fileName)
{
	// Ensure that the file has opened correctly on object creation
	ErrorCheck();
}

#pragma endregion

#pragma region Properties

// Return the address of the file
std::ifstream* FileReader::GetFile() { return &inputFile; }

#pragma endregion

#pragma region Methods

void FileReader::ErrorCheck()
{
	// Open the file in read mode
	inputFile.open(fileName, std::ios::in);

	if(inputFile.is_open())
	{
		std::cout << fileName << " : opened successfully." << std::endl;
	}
	else
	{
		std::cout << fileName << " : cannot be opened." << std::endl;
	}
}

#pragma endregion