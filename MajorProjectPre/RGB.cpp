#include "RGB.h"

#pragma region Constructors

RGB::RGB() : r(0), g(0), b(0) {}

RGB::RGB(unsigned char r, unsigned char g, unsigned char b) 
{
	boundingFlag = false;


	UpperBoundryCheck(Vec3f(r, g, b));

	if(boundingFlag == false)
	{
		LowerBoundryCheck(Vec3f(r, g, b));
	}

}

RGB::RGB(unsigned char* r, unsigned char* g, unsigned char* b)
{
	this->r = *r;
	this->g = *g;
	this->b = *b;
}

RGB::RGB(unsigned char* data, int iterator)
{
	r = data[iterator];
	g = data[iterator + 1];
	b = data[iterator + 2];
}

RGB::RGB(Vec3f value)
{
	boundingFlag = false;

	UpperBoundryCheck(value);

	if(boundingFlag == false)
	{
		LowerBoundryCheck(value);
	}
}

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

#pragma region Methods

Vec3f RGB::operator/(int external)
{
	return Vec3f((float)this->r / external, (float)this->g / external, (float)this->b / external);
}

void RGB::UpperBoundryCheck(Vec3f value)
{
	if(value.GetX() > 255)
	{
		this->r = 255;

		boundingFlag = true;
	}
	else
	{
		this->r = this->r = (unsigned char)value.GetX();
	}

	if(value.GetY() > 255)
	{
		this->g = 255;

		boundingFlag = true;
	}
	else
	{
		this->g = (unsigned char)value.GetY();
	}

	if(value.GetZ() > 255)
	{
		this->b = 255;

		boundingFlag = true;
	}
	else
	{
		this->b = (unsigned char)value.GetZ();
	}

	
}

void RGB::LowerBoundryCheck(Vec3f value)
{

	if(value.GetX() < 0)
	{
		this->r = 0;

		boundingFlag = true;
	}
	else
	{
		this->r = (unsigned char)value.GetX();
	}

	if(value.GetY() < 0)
	{
		this->g = 0;

		boundingFlag = true;
	}
	else
	{
		this->g = (unsigned char)value.GetY();
	}

	if(value.GetZ() < 0)
	{
		this->b = 0;

		boundingFlag = true;
	}
	else
	{
		this->b = (unsigned char)value.GetZ();
	}
}

#pragma endregion
