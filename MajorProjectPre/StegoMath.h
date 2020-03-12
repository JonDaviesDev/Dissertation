#pragma once

#pragma region Preprocessor Directives

#pragma region System Files

#include <iostream>
#include <math.h>

#pragma endregion

#pragma region Project Files

#include "RGB.h"

#pragma endregion

#pragma endregion



class StegoMath
{
#pragma region Constructors

public:
	StegoMath();

#pragma endregion

#pragma region Properties

public:

#pragma endregion

#pragma region Methods

public:
	// Find distance between the pixel and (0, 0, 0)
	float FindLength(RGB pixel);

	int RoundToInt(float value);

	int FindModulus(int distance, int modValue);

	// Find out which side of the midpoint the value sits on
	int DetermineSegment(int remainder, int modValue);

#pragma endregion
};

