#include "BMPInfoHeader.h"

#pragma region Constructors

BMPInfoHeader::BMPInfoHeader(FileReader* reader)
	: bytesPerPixel(3), width(0), height(0), paddingSize(0), reader(reader)
{
	CreateInfoHeader();
}

#pragma endregion

#pragma region Properties

#pragma region Setters

void BMPInfoHeader::SetHeight(int value) { height = value; }

void BMPInfoHeader::SetWidth(int value) { width = value; }

void BMPInfoHeader::SetInfoHeader()
{
	char* buffer = new char[54];

	reader->GetFile()->read(buffer, 54);

	SetWidth(*(int*)&buffer[18]);
	SetHeight(*(int*)&buffer[22]);

	delete[] buffer;
}

void BMPInfoHeader::SetPaddingSize(int value) { paddingSize = value; }

#pragma endregion

#pragma region Getters

int BMPInfoHeader::GetSize() { return infoHeader.size(); }

int BMPInfoHeader::GetBytesPerPixel() { return bytesPerPixel; }

int BMPInfoHeader::GetHeight() { return height; }

int BMPInfoHeader::GetWidth() { return width; }

int BMPInfoHeader::GetPaddingSize() { return paddingSize; }

FileReader* BMPInfoHeader::GetReader() { return reader; }

#pragma endregion

#pragma endregion

#pragma region Methods

void BMPInfoHeader::CreateInfoHeader()
{
	/*
		infoHeader[0]-[3]	= size of header
		infoHeader[4]-[7]	= width of image
		infoHeader[8]-[11]  = height of image
		infoHeader[12]-[13] = number of colour planes
		infoHeader[14]-[15] = number of bits per pixel
		infoHeader[16]-[19] = compression data
		infoHeader[20]-[23] = total image size
		infoHeader[24]-[27] = resolution (horizontal)
		infoHeader[28]-[31] = resolution (vertical)
		infoHeader[32]-[35] = colour table information
		infoHeader[35]-[39] = colour count
	*/

	SetInfoHeader();

	CalculatePaddingSize();

	infoHeader[0] = (unsigned char)(GetSize());				// hs		Set the header size
	infoHeader[4] = (unsigned char)(width);					// w
	infoHeader[5] = (unsigned char)(width >> 8);			// w
	infoHeader[6] = (unsigned char)(width >> 16);			// w		Set the width of the image
	infoHeader[7] = (unsigned char)(width >> 24);			// w
	infoHeader[8] = (unsigned char)(height);				// h
	infoHeader[9] = (unsigned char)(height >> 8);			// h
	infoHeader[10] = (unsigned char)(height >> 16);			// h		Set the height of the image
	infoHeader[11] = (unsigned char)(height >> 24);			// h
	infoHeader[12] = (unsigned char)(1);					// cp		Set the colour plane
	infoHeader[14] = (unsigned char)(bytesPerPixel * 8);	// bpp		Set the number of bits per pixel

}

void BMPInfoHeader::CalculatePaddingSize()
{
	SetPaddingSize((width * 3 + 3) & (~3));
}

#pragma endregion