#include "PixelContainer.h"


#pragma region Constructors

PixelContainer::PixelContainer() : width(0), height(0), r(nullptr), g(nullptr), b(nullptr) {}

PixelContainer::PixelContainer(int size) : width(0), height(0)
{
	r = new unsigned char[size];
	g = new unsigned char[size];
	b = new unsigned char[size];
}

PixelContainer::PixelContainer(int width, int height) : width(width), height(height) 
{
	int size = width * height;

	r = new unsigned char[size];
	g = new unsigned char[size];
	b = new unsigned char[size];
}

#pragma endregion

#pragma region Properties

#pragma region Setters

void PixelContainer::SetWidth(int value) { width = value; }

void PixelContainer::SetHeight(int value) { height = value; }

void PixelContainer::SetRed(unsigned char value, int iterator) { r[iterator] = value; }

void PixelContainer::SetGreen(unsigned char value, int iterator) { g[iterator] = value; }

void PixelContainer::SetBlue(unsigned char value, int iterator) { b[iterator] = value; }

void PixelContainer::SetRed(unsigned char* value, int iterator) { r[iterator] = *value; }

void PixelContainer::SetGreen(unsigned char* value, int iterator) { g[iterator] = *value; }

void PixelContainer::SetBlue(unsigned char* value, int iterator) { b[iterator] = *value; }

#pragma endregion

#pragma region Getters

int PixelContainer::GetWidth() { return width; }

int PixelContainer::GetHeight() { return height; }

unsigned char* PixelContainer::GetRed(int iterator) { return &r[iterator]; }

unsigned char* PixelContainer::GetGreen(int iterator) { return &g[iterator]; }

unsigned char* PixelContainer::GetBlue(int iterator) { return &b[iterator]; }

//std::bitset<1> PixelContainer::GetRedLSB(int iterator){return std::bitset<1>(r) }
//
//std::bitset<1> PixelContainer::GetGreenLSB(int iterator);
//
//std::bitset<1> PixelContainer::GetBlueLSB(int iterator);

#pragma endregion

#pragma endregion

#pragma region Methods

#pragma endregion