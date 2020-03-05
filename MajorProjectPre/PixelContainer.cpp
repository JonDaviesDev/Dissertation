#include "PixelContainer.h"


#pragma region Constructors

PixelContainer::PixelContainer() : width(0), height(0), channels(0), pixelArray(nullptr), r(nullptr), g(nullptr), b(nullptr) {}

PixelContainer::PixelContainer(int width, int height, int channels, bool arraySelector) : width(0), height(0), channels(0), pixelArray(nullptr)
{
	this->width = width;
	this->height = height;
	this->channels = channels;

	if(arraySelector)
	{
		pixelArray = new unsigned char[width * height * channels];

		r = nullptr;
		g = nullptr;
		b = nullptr;
	}
	else
	{
		pixelArray = nullptr;

		r = new unsigned char[width * height * channels];
		g = new unsigned char[width * height * channels];
		b = new unsigned char[width * height * channels];
	}
}

PixelContainer::PixelContainer(int width, int height) : width(width), height(height), pixelArray(nullptr)
{
	int size = width * height;

	r = new unsigned char[size];
	g = new unsigned char[size];
	b = new unsigned char[size];
}


#pragma endregion

#pragma region Properties

#pragma region Setters

void PixelContainer::SetArray(unsigned char* pixelArray) { this->pixelArray = pixelArray; }

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

int PixelContainer::GetChannels() { return channels; }

unsigned char* PixelContainer::GetRed(int iterator) { return &r[iterator]; }

unsigned char* PixelContainer::GetGreen(int iterator) { return &g[iterator]; }

unsigned char* PixelContainer::GetBlue(int iterator) { return &b[iterator]; }

unsigned char* PixelContainer::GetPixelArray() { return pixelArray; }

#pragma endregion

#pragma endregion

#pragma region Methods

#pragma endregion