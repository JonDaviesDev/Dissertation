#include "JPEG.h"


#pragma region Constructors

JPEG::JPEG(JPEGio* jpReader)
{
	Vec3i temp = jpReader->GetImageData()->second;

	pixelList = new PixelContainer(temp.GetX(), temp.GetY(), temp.GetZ(), true);
	
	pixelList->SetArray(jpReader->GetImageData()->first);
}

#pragma endregion

#pragma region Properties

PixelContainer* JPEG::GetPixelList() { return pixelList; }

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