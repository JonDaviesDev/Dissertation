#pragma once
class PixelContainer
{

#pragma region Attributes

private:
	int width;
	int height;

	unsigned char* r;
	unsigned char* g;
	unsigned char* b;

#pragma endregion

#pragma region Constructors

public:
	PixelContainer();

	PixelContainer(int width, int height);

#pragma endregion

#pragma region Properties

#pragma region Setters

	void SetWidth(int value);

	void SetHeight(int value);

	void SetRed(unsigned char value, int iterator);

	void SetGreen(unsigned char value, int iterator);

	void SetBlue(unsigned char value, int iterator);

	void SetRed(unsigned char value);

	void SetGreen(unsigned char value);

	void SetBlue(unsigned char value);

#pragma endregion

#pragma region Getters

	int GetWidth();

	int GetHeight();

	unsigned char* GetRed(int iterator);

	unsigned char* GetGreen(int iterator);

	unsigned char* GetBlue(int iterator);

#pragma endregion
#pragma endregion

};

