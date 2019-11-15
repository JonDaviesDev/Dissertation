#include "RGB.h"

#pragma region Constructors

RGB::RGB() : r(0), g(0), b(0) {}

RGB::RGB(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b) {}

#pragma endregion

#pragma region Properties

// Set & Get Red
void RGB::SetRed(unsigned char value) { r = value; }

unsigned char RGB::GetRed() { return r; }

// Set & Get Green
void RGB::SetGreen(unsigned char value) { g = value; }

unsigned char RGB::GetGreen() { return g; }

// Set & GetBlue
void RGB::SetBlue(unsigned char value) { b = value; }

unsigned char RGB::GetBlue() { return b; }

#pragma endregion