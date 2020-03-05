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
#include "cRGB.h"

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

	std::vector<std::vector<cRGB>> pixelList;

#pragma endregion

#pragma region Constructors

public:
	Stego();

	Stego(FileLoader* coverBMP, FileLoader* textFile, const char* newFileName);

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

	void ModifyBMP(BMP* bmp, const char* newFileName);


	/*---------------- Distance to Origin Utility Functions ----------------*/

	// return value and argument value are temporary just for testing
	int DistanceToOrigin(Pixel pixel, int modulusValue);

	void InitialiseRemainderTable(int startingValue);

	// Find distance between the pixel and (0, 0, 0)
	float FindLength(Pixel pixel);

	int RoundToInt(float value);

	int FindModulus(int distance, int modValue);
	
	// Find out which side of the midpoint the value sits on
	int DetermineSegment(int value, int modValue);

	void CheckEdgesOfScale(int segment, int value, int modValue);

	void ShiftPixelColour();

#pragma endregion
};

