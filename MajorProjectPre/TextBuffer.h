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

	TextBuffer(std::string str);

#pragma endregion

#pragma region Properties

public:
	std::vector<char> GetBuffer();

#pragma endregion

#pragma region Methods

public:
	void ReadFile(FileLoader* textFile);

	void ConvertString(std::string str);

#pragma endregion
};

