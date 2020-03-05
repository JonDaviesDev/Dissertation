#include "Vec3.h"


#pragma region Constructors

Vec3::Vec3() : x(0), y(0), z(0) {}

Vec3::Vec3(int x, int y, int z) : x(x), y(y), z(z) {}

#pragma endregion

#pragma region Properties

Vec3 Vec3::GetValues() { return {x, y, z}; }

int Vec3::GetX() { return x; }

int Vec3::GetY() { return y; }

int Vec3::GetZ() { return z; }

#pragma endregion

#pragma region Methods

bool Vec3::operator==(Vec3 external)
{
	if(this->x == external.x && this->y == external.y && this->z == external.z)
		return true;
	else return false;
}

#pragma endregion