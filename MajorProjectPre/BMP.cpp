#include "BMP.h"


#pragma region Constructors

BMP::BMP() : fileHeader(0), fileInfo() {}

BMP::BMP(FileReader* reader) : fileHeader(0), fileInfo()
{
	
}

#pragma endregion

#pragma region Properties

void BMP::SetHeaderInformation(std::ifstream* fileObject)
{
	char* buffer;

	fileObject->read(buffer, 54);

	fileInfo.SetWidth(*(int*)&buffer[18]);
	height = *(int*)&buffer[22];
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

