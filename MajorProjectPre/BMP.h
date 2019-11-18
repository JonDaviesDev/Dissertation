#pragma once

#pragma region Includes

#pragma region System Files

#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <sstream>

#pragma endregion

#pragma region Project Files

#include "Pixel.h"
#include "BMPFileHeader.h"
#include "BMPInfoHeader.h"
#include "FileReader.h"

#pragma endregion

#pragma endregion

class BMP
{
#pragma region Attributes

private:
	BMPInfoHeader infoHeader;

	//BMPFileHeader fileHeader;
	
	std::vector<Pixel> pixels;

#pragma endregion

#pragma region Constructors

public:

	BMP();

	BMP(FileReader* reader);

#pragma endregion

#pragma region Properties

	void SetInfoHeader(FileReader* reader);

	void SetFileHeader(FileReader* reader, BMPInfoHeader info);

#pragma endregion

#pragma region Methods

	void ScanBMP(std::ifstream* fileObject);


#pragma endregion
};


