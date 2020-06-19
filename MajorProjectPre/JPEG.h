#pragma once
#include "PixelContainer.h"
#include "JPEGio.h"

class JPEG
{
#pragma region Attributes

private:
	const char* fileName;

	PixelContainer* pixelList;

	Vec3i imageData;

#pragma endregion

#pragma region Constructors

public:
	JPEG(JPEGio* jpReader);

	JPEG(JPEGio jpReader, const char* fileName);

#pragma endregion

#pragma region Properties

public:
	PixelContainer* GetPixelList();

	Vec3i GetImageData();

	const char* GetFileName();

#pragma endregion

#pragma region Methods

public:
	void Print();

#pragma endregion
};

