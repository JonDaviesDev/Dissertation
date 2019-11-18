#include "BMP.h"


#pragma region Constructors

BMP::BMP() : infoHeader(nullptr), fileHeader(&infoHeader), fileObject(nullptr) {}

BMP::BMP(FileReader* reader) : infoHeader(reader), fileHeader(&infoHeader), fileObject(reader) 
{
	ScanBMP();

	ReadPixels();
}

#pragma endregion

#pragma region Properties

void BMP::SetPixel(RGB value) { pixels.push_back(Pixel(value)); }

#pragma endregion

#pragma region Methods

void BMP::ScanBMP()
{
	std::string buffer;

	if(fileObject->GetFile()->is_open())
	{
		PrintHeader();
	}
}

void BMP::ReadPixels()
{	
	unsigned char* data = new unsigned char[infoHeader.GetPaddingSize()];

	for(int i = 0; i < infoHeader.GetHeight(); i++)
	{
		//fileObject->GetFile()->getline((char*)data, infoHeader.GetPaddingSize());

		fileObject->GetFile()->read((char*)data, infoHeader.GetPaddingSize());

		for(int j = 0; j < infoHeader.GetWidth() * 3; j += 3)
		{
			ConvertBGRtoRGB(data, j);

			SetPixel(RGB(data, j));
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

