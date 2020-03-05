#include "cRGB.h"

#pragma region Constructors

cRGB::cRGB() : r(0), g(0), b(0) {}

cRGB::cRGB(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b) {}

cRGB::cRGB(unsigned char* data, int iterator)
{
	r = data[iterator];
	g = data[iterator + 1];
	b = data[iterator + 2];
}

#pragma endregion

#pragma region Properties

// Set & Get Red
void cRGB::SetRed(unsigned char value) { r = value; }

unsigned char cRGB::GetRed() { return r; }

// Set & Get Green
void cRGB::SetGreen(unsigned char value) { g = value; }

unsigned char cRGB::GetGreen() { return g; }

// Set & GetBlue
void cRGB::SetBlue(unsigned char value) { b = value; }

unsigned char cRGB::GetBlue() { return b; }

#pragma endregion