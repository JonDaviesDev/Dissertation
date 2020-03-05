#pragma once

class cRGB
{
#pragma region Attributes

private:
	unsigned char r, g, b;

#pragma endregion

#pragma region Constructors

public:
	cRGB();

	cRGB(unsigned char r, unsigned char g, unsigned char b);

	cRGB(unsigned char* data, int iterator);

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

#pragma endregion
};


