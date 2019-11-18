#include "BMP.h"


#pragma region Constructors

BMP::BMP() : infoHeader(nullptr), fileHeader(&infoHeader) {}

BMP::BMP(FileReader* reader) : infoHeader(reader), fileHeader(&infoHeader) {}

#pragma endregion

#pragma region Properties

#pragma endregion

#pragma region Methods

void BMP::ScanBMP(std::ifstream* fileObject)
{
	std::string buffer;

	if(fileObject->is_open())
	{

	}
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

