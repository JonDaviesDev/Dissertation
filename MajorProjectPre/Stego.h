#pragma once

#pragma region Preprocessor Directives

#pragma region System Files

#include <bitset>
#include <cstdlib>

#pragma endregion

#pragma region Project Files

#include "BMPWriter.h"
#include "BMP.h"
#include "TextBuffer.h"
#include "BMPUtility.h"
#include "RGB.h"
#include "Vec3f.h"
#include "StegoMath.h"
#include "Timer.h"

#pragma endregion

#pragma endregion

enum class Direction
{
	SMALLER, LARGER, STAY, UNDEFINED
};



class Stego : public BMPUtility, public StegoMath
{
#pragma region Attributes

private:
	const char* stegoFileName;

	unsigned int informationContainer;

	BMPWriter writer;

	BMP bmp;

	TextBuffer text;

	std::vector<std::bitset<8>> binaryList;

	std::vector<std::vector<RGB>> pixelList;

	float functionTime;

#pragma endregion

#pragma region Constructors

public:
	Stego();

	Stego(FileLoader* coverBMP, FileLoader* textFile, const char* newFileName, Method method, int modValue);

	Stego(FileLoader* coverBMP, std::string* text, const char* newFileName, Method method, int modValue);

#pragma endregion

#pragma region Properties

public:
#pragma region Setters

#pragma endregion

#pragma region Getters

	int GetBinaryListSize();

	const char* GetStegoFileName();

	TextBuffer GetTextBuffer();

	float GetFunctionTime();

#pragma endregion

#pragma endregion

#pragma region Methods

public:
	std::bitset<8> CharToBinary(char value);

	void CreatePixelListCopy();

	void CreateBinaryList(TextBuffer buffer);

	void CreateBinaryList(std::string buffer);

	void BitNumber();

	void LSB();

	void MSB();

	void ModifyBMP(BMP* bmp, const char* newFileName);

	uint32_t PackData(uint8_t pixelsToRead, uint8_t modValue);


	// return value and argument value are temporary just for testing
	void DistanceToOrigin(RGB& pixel, int modulusValue, unsigned long bit);

	std::pair<int, Direction> DistanceToSafeRemainder(int originalRemainder, int segment, unsigned long bitValue, int mod);

	int ModifyDistance(std::pair<int, Direction> value, int distance);

	Vec3f NormaliseDistance(int distance, RGB value);

	Vec3f ScaleVector(Vec3f normalised, int newDistance);
	
#pragma endregion
};

