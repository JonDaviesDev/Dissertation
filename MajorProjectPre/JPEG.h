#pragma once
#include "PixelContainer.h"
#include "JPEGio.h"

class JPEG
{
#pragma region Attributes

private:
	PixelContainer* pixelList;

#pragma endregion

#pragma region Constructors

public:
	JPEG(JPEGio* jpReader);

#pragma endregion

#pragma region Properties

public:
	PixelContainer* GetPixelList();

#pragma endregion

#pragma region Methods

public:
	void Print();

#pragma endregion
};

