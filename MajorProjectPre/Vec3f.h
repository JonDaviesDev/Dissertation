#pragma once

class Vec3f
{
#pragma region Attributes

private:
	float x, y, z;

#pragma endregion

#pragma region Constructors

public:
	Vec3f();

	Vec3f(float x, float y, float z);

	Vec3f(unsigned char x, unsigned char y, unsigned char z);

#pragma endregion

#pragma region Properties

public:
	Vec3f GetValues();

	float GetX();

	float GetY();

	float GetZ();

#pragma endregion

#pragma region Methods

public:
	bool operator==(Vec3f external);
	
	Vec3f operator*(int scalar);

#pragma endregion
};

