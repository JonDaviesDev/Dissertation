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
#include <fstream>


// The testing constructors in the decoder allow for the size of the hidden message to be known

// use this known value to create random series of strings and have to program create, embed, convert and extract automatically

// then store the results in a .csv (results being an accuracy score)

struct Dimension
{
	int x, y;

	Dimension() : x(0), y(0) {}

	Dimension(int x, int y) : x(x), y(y) {}

	Dimension(Vec3i imageData) : x(imageData.GetX()), y(imageData.GetY()) {}

	Dimension(const Dimension& external)
	{
		x = external.x;
		y = external.y;
	}
};

struct Result
{
	int id;

	float score;

	int compressionLevel;

	Dimension dimensions;


	Result() : id(0), score(0), compressionLevel(0), dimensions(0, 0) {}
	Result(int id, float score, int compressionLevel, Dimension imageSize) 
	{
		this->id = id;
		this->score = score;
		this->compressionLevel = compressionLevel;
		this->dimensions = dimensions;
	}
	Result(const Result& external)
	{
		id = external.id;
		score = external.score;
		compressionLevel = external.compressionLevel;
		dimensions = external.dimensions;
	}
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
	Result currentResult;

	std::vector<Result> results;

	std::string currentFilePath;

	std::string decodedMessage;

#pragma endregion

#pragma region Constructors

public:
	Test(int numberOfTests, int compressionRatio);

#pragma endregion

#pragma region Properties

public:

#pragma endregion

#pragma region Methods

public:
	void CreateNewBMP();

	std::string CreateMessage();

	void EmbedBMP(std::string* message);

	JPEG ConvertToJPEG(int compressionLevel);
	
	float CompareResults(std::string originalMessage, std::string decodedMessage);

	void DecodeJPEG(JPEG* jpeg, int messageSize, int compressionRatio, std::string originalMessage);

	void UpdateVector();

	void DeleteImage(std::string fileName);

#pragma endregion
};

