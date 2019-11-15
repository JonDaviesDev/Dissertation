#pragma once
class RGB
{
#pragma region Attributes

private:
	unsigned char r, g, b;

#pragma endregion

#pragma region Constructors

public:
	RGB();

	RGB(unsigned char r, unsigned char g, unsigned char b);

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

