#include "BMP.h"


#pragma region Constructors

BMP::BMP() : infoHeader(nullptr) {}

BMP::BMP(FileReader* reader) : infoHeader(reader)
{
	//SetFileHeader(reader, infoHeader);
}

#pragma endregion

#pragma region Properties



void BMP::SetFileHeader(FileReader* reader, BMPInfoHeader header)
{
	//fileHeader.SetFileName(reader->GetFileName());

	//fileHeader.SetFileSize(infoHeader.GetWidth() * infoHeader.GetHeight() * infoHeader.GetBytesPerPixel());
}


#pragma endregion

#pragma region Methods

void BMP::ScanBMP(std::ifstream* fileObject)
{
	std::string buffer;

	if(fileObject->is_open())
	{

	}
}

#pragma endregion

