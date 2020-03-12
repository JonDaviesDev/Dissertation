#pragma once
#include <iostream>
#include "PixelContainer.h"
#include "FileLoader.h"
#include "Vec3i.h"


class JPEGReader
{
#pragma region Attributes

private:
	FileLoader* file;

	std::pair<unsigned char*, Vec3i>* imageData;
	
#pragma endregion

#pragma region Constructors

public:
	JPEGReader(FileLoader* file);

#pragma endregion

#pragma region Properties

public:
	std::pair<unsigned char*, Vec3i>* GetImageData();

#pragma endregion

#pragma region Methods

public:
	void ReadPixels();

	PixelContainer CopyPixelsToContainer(std::pair<unsigned char*, Vec3i> pixelArray);

#pragma endregion
};

