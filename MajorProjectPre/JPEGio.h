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
	const char* fileName;

	FileLoader* file;

	std::pair<unsigned char*, Vec3i>* imageData;
	
#pragma endregion

#pragma region Constructors

public:
	JPEGio();

	JPEGio(FileLoader* file);

	JPEGio(BMP* bmp, int compressionLevel);

	JPEGio(BMP bmp, int compressionLevel);

#pragma endregion

#pragma region Properties

public:
	std::pair<unsigned char*, Vec3i>* GetImageData();

	const char* GetFileName();

#pragma endregion

#pragma region Methods

public:
	void ReadPixels();

	PixelContainer CopyPixelsToContainer(std::pair<unsigned char*, Vec3i> pixelArray);

	void WriteJPEG(const char* name, int width, int height, int channels, PixelContainer* pixels, int quality);

	void BMPtoJPEG(BMP* bmp, int compressionLevel);

	std::string ChangeExtension(const char* fileName, const char* newExtension);

#pragma endregion
};

