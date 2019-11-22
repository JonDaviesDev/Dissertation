#include "BMP.h"


#pragma region Constructors

BMP::BMP() : infoHeader(nullptr), fileHeader(&infoHeader), fileObject(nullptr), pixels() {}

BMP::BMP(FileReader* reader) : fileHeader(&infoHeader), infoHeader(reader), fileObject(reader)
{
	pixels = {infoHeader.GetWidth(), infoHeader.GetHeight()};

	ScanBMP();

	ReadPixels();
}

#pragma endregion

#pragma region Properties

#pragma region Setters


#pragma endregion

#pragma region Getters

int BMP::GetHeight() { return infoHeader.GetHeight(); }

int BMP::GetWidth() { return infoHeader.GetWidth(); }

int BMP::GetColourSpace() { return infoHeader.GetBytesPerPixel(); }

#pragma endregion

#pragma endregion

#pragma region Methods

void BMP::ScanBMP()
{
	const char* buffer;

	if(fileObject->GetFile())
	{
		PrintHeader();
	}
}

void BMP::ReadPixels()
{
	unsigned char* data = new unsigned char[infoHeader.GetPaddingSize()];

	for(int i = 0; i < infoHeader.GetHeight(); i++)
	{
		fileObject->ErrorCheck(fileObject->GetFile(), fileObject->GetFileName(), "r");

		fread(data, sizeof(unsigned char), infoHeader.GetPaddingSize(), fileObject->GetFile());

		for(int j = 0; j < infoHeader.GetWidth() * 3; j += 3)
		{
			pixels.SetRed(data[j], j);
			pixels.SetGreen(data[j + 1], j + 1);
			pixels.SetBlue(data[j + 2], j + 2);
		}
	}
}

void BMP::ConvertBGRtoRGB(unsigned char* data, int iteration)
{
	unsigned char temp = 0;

	temp = data[iteration];
	data[iteration] = data[iteration + 2];
	data[iteration + 2] = temp;
}

#pragma region Display Functions

void BMP::PrintHeader()
{
	std::cout << std::endl << "Image width: " << infoHeader.GetWidth() << std::endl;
	std::cout << "Image height: " << infoHeader.GetHeight() << std::endl;
	std::cout << "Image size: " << fileHeader.GetFileSize() << " bytes" << std::endl << std::endl;
}

#pragma endregion

#pragma endregion

