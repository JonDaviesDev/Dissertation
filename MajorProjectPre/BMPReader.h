#pragma once
#include <iostream>
#include "BMP.h"

class BMPReader
{

#pragma region Attributes

private:
	FILE* fileObject;

#pragma endregion

#pragma region Constructors

public:
	BMPReader(BMP* bmp);

#pragma endregion

#pragma region Properties

public:

#pragma endregion

#pragma region Methods

public:
	BMP* CloneBMP(BMP* bmp);

#pragma endregion
};
	
