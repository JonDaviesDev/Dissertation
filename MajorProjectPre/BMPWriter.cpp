#include "BMPWriter.h"


#pragma region Constructors

BMPWriter::BMPWriter() 
	: fileName(nullptr), fileObject(nullptr), height(0), width(0), colourSpace(0), bmp(nullptr) {}

BMPWriter::BMPWriter(BMP* bmp) 
	: fileName(nullptr), fileObject(nullptr), height(bmp->GetHeight()), 
	width(bmp->GetWidth()), colourSpace(bmp->GetColourSpace()), bmp(bmp) {}

#pragma endregion

#pragma region Properties

#pragma region Setters

void BMPWriter::SetHeight(int value) { height = value; }

void BMPWriter::SetWidth(int value) { width = value; }

void BMPWriter::SetColourSpace(int value) { colourSpace = value; }

#pragma endregion

#pragma region Getters

int BMPWriter::GetHeight() { return height; }

int BMPWriter::GetWidth() { return width; }

int BMPWriter::GetColourSpace() { return colourSpace; }

const char* BMPWriter::GetFileName() { return fileName; }

#pragma endregion

#pragma endregion

#pragma region Methods

void BMPWriter::CreateNewBMP(const char* fileName, int width, int height, cRGB colour)
{
	PixelContainer pixelContainer(width, height);

	for(int i = 0; i < height * width; i++)
	{
		pixelContainer.SetRed((unsigned char)colour.GetRed(), i);
		pixelContainer.SetGreen((unsigned char)colour.GetGreen(), i);
		pixelContainer.SetBlue((unsigned char)colour.GetBlue(), i);
	}

	GenerateImageData(fileObject ,pixelContainer, height, width, fileName);

	std::cout << "Image generated" << std::endl;
}

void BMPWriter::CloneBMP(BMP* bmp, const char* newFileName)
{
	PixelContainer pixelContainer(bmp->GetWidth(), bmp->GetHeight());

	for(int i = 0; i < bmp->GetHeight() * bmp->GetWidth(); i++)
	{
		pixelContainer.SetRed((unsigned char*)bmp->GetPixelContainer()->GetRed(i), i);
		pixelContainer.SetGreen((unsigned char*)bmp->GetPixelContainer()->GetGreen(i), i);
		pixelContainer.SetBlue((unsigned char*)bmp->GetPixelContainer()->GetBlue(i), i);
	}

	GenerateImageData(bmp, pixelContainer, newFileName);

	std::cout << "Image generated" << std::endl;

	fclose(bmp->GetFileObject()->GetFile());
}

void BMPWriter::ConvertBGRtoRGB(unsigned char* data, int iteration)
{
	unsigned char temp = 0;

	temp = data[iteration];
	data[iteration] = data[iteration + 2];
	data[iteration + 2] = temp;
}

#pragma endregion
