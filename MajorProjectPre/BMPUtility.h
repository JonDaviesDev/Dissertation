#pragma once
#pragma region Preprocessor Directives

#pragma region System Files



#pragma endregion

#pragma region Project Files

#include "BMP.h"
#include "FileLoader.h"

#pragma endregion

#pragma endregion

class BMPUtility : public FileLoader
{
	// This class provides base functionality for any classes that implement it

#pragma region Attributes

private:


#pragma endregion

#pragma region Constructors


#pragma endregion

#pragma region Properties

public:

#pragma endregion

#pragma region Methods

public:	
	unsigned char* CreateFileHeader(int height, int width, int paddingSize);

	unsigned char* CreateInfoHeader(int height, int width);

	void GenerateImageData(FILE* fileObject, PixelContainer image, int height, int width, const char* imageFileName);

	void GenerateImageData(BMP* bmp, PixelContainer pixelContainer, const char* newFileName);

#pragma endregion
};

