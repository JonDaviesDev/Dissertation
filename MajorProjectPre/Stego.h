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
#include "RGB.h"

#pragma endregion

#pragma endregion

class Stego : public BMPUtility
{
#pragma region Attributes

private:
	const char* stegoFileName;

	BMPWriter writer;

	BMP bmp;

	TextBuffer text;

	std::vector<std::bitset<8>> binaryList;

	std::vector<std::vector<RGB>> pixelList;

#pragma endregion

#pragma region Constructors

public:
	Stego();

	Stego(FileReader* coverBMP, FileReader* textFile, const char* newFileName);

#pragma endregion

#pragma region Properties

public:
#pragma region Setters

#pragma endregion

#pragma region Getters

	int GetBinaryListSize();

	const char* GetStegoFileName();

#pragma endregion

#pragma endregion

#pragma region Methods

public:
	std::bitset<8> CharToBinary(char value);

	void CreatePixelListCopy();

	void CreateBinaryList(TextBuffer buffer);

	void BitNumber();

	void LSB();

	void DistanceToOrigin();

	void ModifyBMP(BMP* bmp, const char* newFileName);

private:
	float FindLength(Pixel pixel);

	int RoundToInt(float value);

	int FindModulus(int distance, int modValue);

	void CheckForFringeValues(int value, int modValue);

	void ShiftPixelColour();

#pragma endregion
};

