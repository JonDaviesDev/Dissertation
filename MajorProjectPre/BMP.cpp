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

#pragma region Setters

void BMP::SetPixel(unsigned char* value, int iterator) 
{ 
	//testImage.push_back(std::vector<std::vector<Pixel>>(infoHeader.GetWidth(), std::vector<Pixel>(1, (RGB(value, iterator)))));

	//testImage = {(std::vector<std::vector<std::vector<Pixel>>>(infoHeader.GetHeight(), std::vector<std::vector<Pixel>>(infoHeader.GetWidth(), std::vector<Pixel>(1, RGB(value, iterator)))))};
}

void BMP::SetPixelData(unsigned char* data, int iterator)
{
	//testImage.push_back(Pixel(data, iterator));
}

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
	std::string buffer;

	if(fileObject->GetFile()->is_open())
	{
		PrintHeader();
	}
}

void BMP::ReadPixels()
{	
	unsigned char* data = new unsigned char[infoHeader.GetPaddingSize()];

	int i, j;

	//image = std::vector<std::vector<Pixel>>(infoHeader.GetHeight(), std::vector<Pixel>(infoHeader.GetWidth(), Pixel(RGB())));

	for(i = 0; i < infoHeader.GetHeight(); i++)
	{
		fileObject->GetFile()->readsome((char*)data, infoHeader.GetPaddingSize());

		for(j = 0; j < infoHeader.GetWidth() * 3; j++)
		{
			ConvertBGRtoRGB(data, j);

			//SetPixelData(data, j);


			// All of it not working!!!!!!
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

