#include "Vec3i.h"


#pragma region Constructors

Vec3i::Vec3i() : x(0), y(0), z(0) {}

Vec3i::Vec3i(int x, int y, int z) : x(x), y(y), z(z) {}

#pragma endregion

#pragma region Properties

void Vec3i::SetValues(Vec3i values)
{
	this->x = values.x;
	this->y = values.y;
	this->z = values.z;
}

void Vec3i::SetX(int x) { this->x = x; }

void Vec3i::SetY(int y) { this->y = y; }

void Vec3i::SetZ(int z) { this->z = z; }

Vec3i Vec3i::GetValues() { return {x, y, z}; }

int Vec3i::GetX() { return x; }

int Vec3i::GetY() { return y; }

int Vec3i::GetZ() { return z; }

#pragma endregion

#pragma region Methods

bool Vec3i::operator==(Vec3i external)
{
	if(this->x == external.x && this->y == external.y && this->z == external.z)
		return true;
	else return false;
}

#pragma endregion