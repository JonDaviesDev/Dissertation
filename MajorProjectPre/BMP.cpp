#include "BMP.h"


#pragma region Constructors

BMP::BMP() : infoHeader(nullptr), fileHeader(&infoHeader), fileObject(nullptr), pixels() {}

BMP::BMP(FileLoader* reader) : fileHeader(&infoHeader), infoHeader(reader), fileObject(reader)
{
	// Open the file after perfoming a check to see if the file can be found/accessed
	fileObject->ErrorCheck(fileObject->GetFile(), fileObject->GetFileName(), "r");

	// Assign the size of the pixel container
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

FileLoader* BMP::GetFileObject() { return fileObject; }

BMPInfoHeader* BMP::GetInfoHeader() { return &infoHeader; }

BMPFileHeader* BMP::GetFileHeader() { return &fileHeader; }

PixelContainer* BMP::GetPixelContainer() { return &pixels; }

#pragma endregion

#pragma endregion

#pragma region Methods

void BMP::ScanBMP()
{
	const char* buffer;

	// Print file information
	if(fileObject->GetFile())
	{
		PrintHeader();
	}
}

void BMP::ReadPixels()
{
	unsigned char* data = new unsigned char[infoHeader.GetPaddingSize()];

	int k = 0;

	// Iterate through all the rows of the image
	for(int i = 0; i < infoHeader.GetHeight(); i++)
	{
		// Read the current line of pixels of the image
		fread(data, sizeof(unsigned char), infoHeader.GetPaddingSize(), fileObject->GetFile());

		// Iterate through all the colums of the image
		for(int j = 0; j < infoHeader.GetWidth() * 3; j+=3)
		{
			// Conversion
			ConvertBGRtoRGB(data, j);

			pixels.SetRed(data[j], k);

			pixels.SetGreen(data[j + 1], k);

			pixels.SetBlue(data[j + 2], k);

			k++;
		}

	}

}

// Covert from Windows' native BGR to RGB
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

void BMP::PrintPixels()
{
	std::cout << std::endl;

	for(int i = 0; i < infoHeader.GetHeight(); i++)
	{
		for(int j = 0; j < infoHeader.GetWidth(); j++)
		{
			std::cout << (int)pixels.GetRed(i)[j] << ", ";
			std::cout << (int)pixels.GetGreen(i)[j] << ", ";
			std::cout << (int)pixels.GetBlue(i)[j] << std::endl;
		}
	}
}

void BMP::ImageBitRepresentation()
{
	std::cout << std::endl;

	for(int i = 0; i < infoHeader.GetHeight(); i+=3)
	{
		for(int j = 0; j < infoHeader.GetWidth(); j+=3)
		{
			if((int)pixels.GetRed(i)[j] == 255)
			{
				std::cout << 1;
			}
			
			{
				std::cout << 0;
			}
		}

		std::cout << std::endl;
	}
}

#pragma endregion

#pragma endregion

