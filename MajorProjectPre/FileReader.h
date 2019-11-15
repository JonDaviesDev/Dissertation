#pragma once

#pragma region Includes

#include <iostream>
#include <fstream>

#pragma endregion


class FileReader
{
#pragma region Attributes

private:
	std::ifstream inputFile;

	std::string fileName;

#pragma endregion

#pragma region Constructors

public:
	FileReader(std::string fileName);

#pragma endregion

#pragma region Properties

public:
	std::ifstream* GetFile();

#pragma endregion

#pragma region Methods

public:
	void ErrorCheck();



#pragma endregion
};

