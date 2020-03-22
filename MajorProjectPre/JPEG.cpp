#include "JPEG.h"


#pragma region Constructors

JPEG::JPEG(JPEGio* jpReader)
{
	fileName = jpReader->GetFileName();

	imageData = jpReader->GetImageData()->second;

	pixelList = new PixelContainer(imageData.GetX(), imageData.GetY(), imageData.GetZ(), true);
	
	pixelList->SetArray(jpReader->GetImageData()->first);
}

JPEG::JPEG(JPEGio jpReader, const char* fileName)
{
	this->fileName = fileName;

	imageData = jpReader.GetImageData()->second;

	pixelList = new PixelContainer(imageData.GetX(), imageData.GetY(), imageData.GetZ(), true);

	pixelList->SetArray(jpReader.GetImageData()->first);
}

#pragma endregion

#pragma region Properties

PixelContainer* JPEG::GetPixelList() { return pixelList; }

Vec3i JPEG::GetImageData() { return imageData; }

const char* JPEG::GetFileName() { return fileName; }

#pragma endregion

#pragma region Methods

void JPEG::Print()
{
	int size = pixelList->GetWidth() * pixelList->GetHeight() * pixelList->GetChannels();

	for(int i = 0; i < size; i+=3)
	{
		std::cout << (int)pixelList->GetPixelArray()[i] << ", " << (int)pixelList->GetPixelArray()[i + 1] << ", " << (int)pixelList->GetPixelArray()[i + 2] << std::endl;
	}
}

#pragma endregion