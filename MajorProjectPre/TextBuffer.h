#pragma once
#include "FileLoader.h"
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

	TextBuffer(FileLoader* textFile);

#pragma endregion

#pragma region Properties

public:
	std::vector<char> GetBuffer();

#pragma endregion

#pragma region Methods

public:
	void ReadFile(FileLoader* textFile);

#pragma endregion
};

