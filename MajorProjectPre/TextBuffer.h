#pragma once
#include "FileReader.h"
#include <vector>

class TextBuffer
{
#pragma region Attributes

private:
	std::vector<char> buffer;

#pragma endregion

#pragma region Constructors

public:
	TextBuffer();

	TextBuffer(FileReader* textFile);

#pragma endregion

#pragma region Properties

public:
	std::vector<char> GetBuffer();

#pragma endregion

#pragma region Methods

public:
	void ReadFile(FileReader* textFile);

#pragma endregion
};

