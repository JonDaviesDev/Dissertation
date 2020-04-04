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

	float accuracy;

	int matchedCharacters;

	int totalCharacters;

	int compressionLevel;

	Dimension imageDimensions;

	std::string originalMessage;

	std::string decodedMessage;

	Result() : id(0), accuracy(0), matchedCharacters(0), compressionLevel(0), imageDimensions(0, 0) {}
	Result(int id, float acc, int mc, int tc, int compressionLevel, Dimension imageSize, std::string om, std::string dm) 
	{
		this->id = id;
		this->accuracy = acc;
		this->matchedCharacters = mc;
		this->totalCharacters = tc;
		this->compressionLevel = compressionLevel;
		this->imageDimensions = imageSize;
		this->originalMessage = om;
		this->decodedMessage = dm;
	}
	Result(const Result& external)
	{
		id = external.id;
		accuracy = external.accuracy;
		matchedCharacters = external.matchedCharacters;
		totalCharacters = external.totalCharacters;
		compressionLevel = external.compressionLevel;
		imageDimensions = external.imageDimensions;
		originalMessage = external.originalMessage;
		decodedMessage = external.decodedMessage;
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

	int matchedCharacters;

	int totalCharacters;

	std::vector<Result> results;

	std::string currentFilePath;

	std::string decodedMessage;

#pragma endregion

#pragma region Constructors

public:
	Test();

	Test(int numberOfTests, int compressionRatio, Method method, std::string customMessage = "");

	Test(int numberOfTests, int compressionRatio, int modulusValue, Method method, std::string customMessage = "");

#pragma endregion

#pragma region Properties

public:
	std::vector<Result> GetList();

	Result* GetResults();

#pragma endregion

#pragma region Methods

public:
	void CreateNewBMP();

	std::string CreateMessage();

	void EmbedBMP(std::string* message);

	JPEG ConvertToJPEG(int compressionLevel);
	
	float CompareResults(std::string originalMessage, std::string decodedMessage);

	void DecodeJPEG(JPEG* jpeg, int messageSize, int compressionRatio, Method method, std::string originalMessage);

	void UpdateVector();

	float AverageResults();

	void DeleteImage(std::string fileName);

#pragma endregion
};

