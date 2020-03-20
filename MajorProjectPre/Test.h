#pragma once

#include <vector>
#include <random>
#include <iostream>

#include "BMP.h"
#include "JPEGio.h"
#include "JPEG.h"
#include "BMPWriter.h"
#include "Decoder.h"
#include "TextBuffer.h"
#include "Stego.h"


// The testing constructors in the decoder allow for the size of the hidden message to be known

// use this known value to create random series of strings and have to program create, embed, convert and extract automatically

// then store the results in a .csv (results being an accuracy score)

struct Dimension
{
	int x, y;

	Dimension() : x(0), y(0) {}

	Dimension(int x, int y) : x(x), y(y) {}

	Dimension(Vec3i imageData) : x(imageData.GetX()), y(imageData.GetY()) {}
};

struct Result
{
	int id;

	float score;

	int compressionLevel;

	Dimension dimensions;


	Result() : id(0), score(0), compressionLevel(0), dimensions(0, 0) {}
	Result(float score, int compressionLevel, Dimension imageSize) {}
};

static struct Random
{
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_int_distribution<int> dist;
	int value;

	Random() {}
	Random(int min, int max) : rng(rd()), dist(min, max) 
	{
		value = dist(rng);
	}

	int Generate(int min) { return dist(rng); }
};




class Test
{
#pragma region Attributes

public:
	std::vector<Result> results;


#pragma endregion

#pragma region Constructors

public:
	Test(int numberOfTests);

#pragma endregion

#pragma region Properties

public:

#pragma endregion

#pragma region Methods

public:
	BMP* CreateNewBMP();

	std::string* CreateMessage();

	BMP* EmbedBMP(BMP* bmp, std::string* message);

	JPEG* ConvertToJPEG(BMP* bmp);
	
	float CompareResults(std::string originalMessage, std::string decodedMessage);

	Result DecodeJPEG(JPEG* jpeg, int messageSize, std::string originalMessage);

	void UpdateVector(Result result);


#pragma endregion
};

