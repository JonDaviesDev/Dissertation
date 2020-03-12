#pragma once

class Vec3i
{
#pragma region Attributes

private:
	int x, y, z;

#pragma endregion

#pragma region Constructors

public:
	Vec3i();

	Vec3i(int x, int y, int z);

#pragma endregion

#pragma region Properties

public:
	Vec3i GetValues();

	int GetX();

	int GetY();

	int GetZ();

#pragma endregion

#pragma region Methods

public:

	bool operator==(Vec3i external);

#pragma endregion
};

