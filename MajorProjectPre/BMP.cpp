#include "BMP.h"


#pragma region Constructors

BMP::BMP() : infoHeader(nullptr), fileHeader(&infoHeader), fileObject(nullptr), pixels() {}

BMP::BMP(FileReader* reader) : fileHeader(&infoHeader), infoHeader(reader), fileObject(reader)
{
	fileObject->ErrorCheck(fileObject->GetFile(), fileObject->GetFileName(), "r");

	pixels = {infoHeader.GetWidth(), infoHeader.GetHeight()};

	ScanBMP();

	ReadPixels();
}

#pragma endregion

#pragma region Properties

#pragma region Setters

void BMP::SetPixelContainer(PixelContainer pixelList) { pixels = pixelList; }

#pragma endregion

#pragma region Getters

int BMP::GetHeight() { return infoHeader.GetHeight(); }

int BMP::GetWidth() { return infoHeader.GetWidth(); }

int BMP::GetColourSpace() { return infoHeader.GetBytesPerPixel(); }

FileReader* BMP::GetFileObject() { return fileObject; }

BMPInfoHeader* BMP::GetInfoHeader() { return &infoHeader; }

BMPFileHeader* BMP::GetFileHeader() { return &fileHeader; }

PixelContainer* BMP::GetPixelContainer() { return &pixels; }

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

	int k = 0;

	for(int i = 0; i < infoHeader.GetHeight(); i++)
	{
		fread(data, sizeof(unsigned char), infoHeader.GetPaddingSize(), fileObject->GetFile());

		for(int j = 0; j < infoHeader.GetWidth(); j++)
		{
			ConvertBGRtoRGB(data, k);

			pixels.SetRed(data[k], j);
			pixels.SetGreen(data[k + 1], j);
			pixels.SetBlue(data[k + 2], j);

			k += 3;
		}

		k = 0;
	
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

