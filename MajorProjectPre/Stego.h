#pragma once

#pragma region Preprocessor Directives

#pragma region System Files

#include <bitset>

#pragma endregion

#pragma region Project Files

#include "BMPWriter.h"
#include "BMP.h"
#include "TextBuffer.h"
#include "BMPUtility.h"

#pragma endregion

#pragma endregion

class Stego : public BMPUtility
{
#pragma region Attributes

private:
	BMPWriter writer;

	BMP bmp;

	TextBuffer text;

	std::vector<std::bitset<8>> binaryList;

#pragma endregion

#pragma region Constructors

public:
	Stego();

	Stego(FileReader* coverBMP, FileReader* textFile);

#pragma endregion

#pragma region Properties

public:
#pragma region Setters

#pragma endregion

#pragma region Getters

#pragma endregion

#pragma endregion

#pragma region Methods

public:
	std::bitset<8> CharToBinary(char value);

	void CreateBinaryList(TextBuffer buffer);

	void ModifyBMP(BMP* bmp, const char* newFileName);


#pragma endregion
};

