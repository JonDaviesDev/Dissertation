#pragma once
class Vec3
{
#pragma region Attributes

private:
	int x, y, z;

#pragma endregion

#pragma region Constructors

public:
	Vec3();

	Vec3(int x, int y, int z);

#pragma endregion

#pragma region Properties

public:
	Vec3 GetValues();

	int GetX();

	int GetY();

	int GetZ();

#pragma endregion

#pragma region Methods

public:

	bool operator==(Vec3 external);

#pragma endregion
};

