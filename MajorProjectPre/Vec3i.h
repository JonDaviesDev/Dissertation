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
	void SetValues(Vec3i values);

	void SetX(int x);

	void SetY(int y);

	void SetZ(int z);

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

