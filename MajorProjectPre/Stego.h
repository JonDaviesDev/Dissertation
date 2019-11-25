#pragma once

#include "BMPWriter.h"
#include "BMP.h"

class Stego
{
#pragma region Attributes

private:
	BMPWriter writer;

	BMP bmp;

	FILE* coverObject;

	FILE* hiddenObject;

	const char* coverFilePath;

	const char* textFilePath;

#pragma endregion

#pragma region Constructors

public:
	Stego();

	Stego(const char* coverBMP, const char* textFile);

#pragma endregion

#pragma region Properties

public:
#pragma region Setters

#pragma endregion

#pragma region Getters

	BMPWriter GetWriter();

	FILE* GetCoverFile();

	FILE* GetTextFile();

#pragma endregion

#pragma endregion

#pragma region Methods

public:
	void Cloner();

#pragma endregion
};

