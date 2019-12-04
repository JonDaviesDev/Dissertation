#pragma once

#pragma region Preprocessor Directives

#pragma region System Files

#include <iostream>

#pragma endregion

#pragma region Project Files

#include "BMP.h"

#pragma endregion

#pragma endregion

class Decoder
{
#pragma region Attributes

private:
	FILE* newTextFile;
	
	BMP* stegoImage;

#pragma endregion

#pragma region Constructors

public:
	Decoder(BMP* stegoImage);

#pragma endregion

#pragma region Properties

public:

#pragma endregion

#pragma region Methods

public:
	void RetrieveMessage();

#pragma endregion
};

