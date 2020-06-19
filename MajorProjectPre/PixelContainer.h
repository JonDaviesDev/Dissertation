#pragma once

#pragma region Preprocessor Directives

#include <bitset>

#pragma endregion

class PixelContainer
{

#pragma region Attributes

private:
	int width;
	int height;
	int channels;

	unsigned char* pixelArray;

	unsigned char* r;
	unsigned char* g;
	unsigned char* b;

#pragma endregion

#pragma region Constructors

public:
	PixelContainer();

	PixelContainer(int width, int height, int channels, bool arraySelector);

	PixelContainer(int width, int height);

#pragma endregion

#pragma region Properties

#pragma region Setters

	void SetArray(unsigned char* pixelArray);

	void SetWidth(int value);

	void SetHeight(int value);

	void SetRed(unsigned char value, int iterator);

	void SetGreen(unsigned char value, int iterator);

	void SetBlue(unsigned char value, int iterator);

	void SetRed(unsigned char* value, int iterator);

	void SetGreen(unsigned char* value, int iterator);

	void SetBlue(unsigned char* value, int iterator);

#pragma endregion

#pragma region Getters

	int GetWidth();

	int GetHeight();

	int GetChannels();

	unsigned char* GetRed(int iterator);

	unsigned char* GetGreen(int iterator);

	unsigned char* GetBlue(int iterator);

	unsigned char* GetPixelArray();

	/*std::bitset<1> GetRedLSB(int iterator);

	std::bitset<1> GetGreenLSB(int iterator);

	std::bitset<1> GetBlueLSB(int iterator);*/

#pragma endregion
#pragma endregion

};

