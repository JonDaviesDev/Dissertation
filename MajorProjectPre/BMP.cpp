#include "BMP.h"


#pragma region Constructors

BMP::BMP() : fileInfo(), fileHeader(0) {}

BMP::BMP(FileReader* reader) :  fileHeader(0), fileInfo()
{
	SetHeaders(reader);
}

#pragma endregion

#pragma region Properties

void BMP::SetHeaders(FileReader* reader)
{
	char* buffer = nullptr;

	reader->GetFile()->read(buffer, 54);

	fileHeader.SetFileName(reader->GetFileName());

	fileInfo.SetWidth(*(int*)&buffer[18]);
	fileInfo.SetHeight(*(int*)&buffer[22]);

	fileHeader.SetFileSize(fileInfo.GetWidth() * fileInfo.GetHeight() * fileInfo.GetBytesPerPixel());
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

