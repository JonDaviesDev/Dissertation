#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <stdarg.h>
#include "Test.h"


struct ExportData
{
	int testNumber;

	float compressionLevel;
	
	int numberOfTests;
	
	float data;

	int originalCharacterCount;

	int matchedCharacterCount;


	ExportData() 
		: testNumber(0), compressionLevel(0), numberOfTests(0), data(0), originalCharacterCount(0), matchedCharacterCount(0) 
	{}

	ExportData(int testNumber, float compressionLevel, int numberOfTests, float data, int originalCharacterCount, int matchedCharacterCount)
		: testNumber(testNumber), compressionLevel(compressionLevel), numberOfTests(numberOfTests), data(data), originalCharacterCount(originalCharacterCount), matchedCharacterCount(matchedCharacterCount)
	{}
};


class Exporter
{
#pragma region Attributes

private:
	std::ofstream out;

	std::string filename;

	std::vector<ExportData> exportData;

#pragma endregion

#pragma region Constructors

public:

	Exporter(const std::string& outputFile);

	Exporter(const std::vector<Result>& resultList, const std::string& outputFile);

#pragma endregion

#pragma region Properties

public:
	std::fstream* GetFile();

	std::string GetName();

#pragma endregion

#pragma region Methods

public:
	void Open(std::string filename);

	void Close();

	void AddData(int testNumber, float compressionLevel, int numberOfTests, float data, int originalCharacterCount, int MatchedCharaterCount);

	void PrintHeading();

	void Write();

#pragma endregion
};

