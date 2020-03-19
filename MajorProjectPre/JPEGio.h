#pragma once
#include <iostream>
#include "PixelContainer.h"
#include "FileLoader.h"
#include "Vec3i.h"
#include "BMP.h"
#include <filesystem>


class JPEGio
{
#pragma region Attributes

private:
	FileLoader* file;

	std::pair<unsigned char*, Vec3i>* imageData;
	
#pragma endregion

#pragma region Constructors

public:
	JPEGio();

	JPEGio(FileLoader* file);

#pragma endregion

#pragma region Properties

public:
	std::pair<unsigned char*, Vec3i>* GetImageData();

#pragma endregion

#pragma region Methods

public:
	void ReadPixels();

	PixelContainer CopyPixelsToContainer(std::pair<unsigned char*, Vec3i> pixelArray);

	void WriteJPEG(std::string name, int width, int height, int channels, PixelContainer* pixels, int quality);

	void BMPtoJPEG(BMP* bmp);

	std::string ChangeExtension(const char* fileName, const char* newExtension);

#pragma endregion
};

