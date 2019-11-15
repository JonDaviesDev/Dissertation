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

#pragma endregion

#pragma endregion

class BMP
{
#pragma region Attributes

private:
	BMPFileHeader fileHeader;
	
	BMPInfoHeader fileInfo;

	std::vector<Pixel> pixels;

#pragma endregion

#pragma region Constructors

public:

	BMP();

#pragma endregion

#pragma region Properties

	void SetHeaderInfomation(char* bmpHeaderInfo, const char* filePath, FILE* file);

	void SetPixelData(unsigned char* data, int iterator);

	void SetPixelData(BMP* bmp, unsigned char* data, int iterator);

#pragma endregion

#pragma region Methods

	BMP* ScanBMP(const char* filePath, const char* openMode);

	FILE* LoadBMP(BMP& bmp, const char* openMode);

	unsigned int CalculatePadding();

	void ReadPixels(FILE* file);

	void ConvertBGRtoRGB(unsigned char* data, int iteration);

	FILE* ErrorCheck(FILE* file, const char* filePath, const char* mode);

	//void WriteToBMP(BMP& bmp);

	void Write(const char* fileName);

	void Write(BMP bmp);

	void generateBitmapImage(unsigned char* image, int height, int width, const char* imageFileName);

	void GenerateBitmapImage(std::vector<std::vector<std::vector<unsigned char>>> image, BMP bmp);

	unsigned char* createBitmapFileHeader(int height, int width, int paddingSize);

	unsigned char* createBitmapInfoHeader(int height, int width);

	std::bitset<8> GetBinary8(unsigned char p);

	std::string ReadTextFile();

#pragma region DisplayFunctions

	void DisplayHeaderInformation();

	void DisplayRGBValues(unsigned char* data, int& iteration);

	void DisplayHexValues(unsigned char* data, int& iteration, int& pixels);

	void DisplayBinaryTest(unsigned char p);

#pragma endregion


#pragma endregion
};


