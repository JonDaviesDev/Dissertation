#pragma once
#include "Vec3f.h"

class RGB
{
#pragma region Attributes

private:
	unsigned char r, g, b;

	bool boundingFlag;

#pragma endregion

#pragma region Constructors

public:
	RGB();

	RGB(unsigned char r, unsigned char g, unsigned char b);

	RGB(unsigned char* r, unsigned char* g, unsigned char* b);

	RGB(unsigned char* data, int iterator);

	RGB(Vec3f value);

#pragma endregion

#pragma region Properties

public:

	void SetRed(unsigned char value);

	unsigned char GetRed();

	void SetGreen(unsigned char value);

	unsigned char GetGreen();

	void SetBlue(unsigned char value);

	unsigned char GetBlue();

#pragma endregion

#pragma region Methods

public:
	Vec3f operator/(int external);

	void UpperBoundryCheck(Vec3f value);

	void LowerBoundryCheck(Vec3f value);

#pragma endregion
};


