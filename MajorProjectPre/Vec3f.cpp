#include "Vec3f.h"

#pragma region Constructors

Vec3f::Vec3f() : x(0), y(0), z(0) {}

Vec3f::Vec3f(float x, float y, float z) : x(x), y(y), z(z) {}

Vec3f::Vec3f(unsigned char x, unsigned char y, unsigned char z)
{
	this->x = (float)x;
	this->y = (float)y;
	this->z = (float)z;
}

#pragma endregion

#pragma region Properties

Vec3f Vec3f::GetValues() { return {x, y, z}; }

float Vec3f::GetX() { return x; }

float Vec3f::GetY() { return y; }

float Vec3f::GetZ() { return z; }

#pragma endregion

#pragma region Methods

bool Vec3f::operator==(Vec3f external)
{
	if(this->x == external.x && this->y == external.y && this->z == external.z)
		return true;
	else return false;
}

Vec3f Vec3f::operator*(int scalar)
{
	return Vec3f(this->x * scalar, this->y * scalar, this->z * scalar);
}

#pragma endregion