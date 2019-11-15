#include "BMPFileHeader.h"

#pragma region Constructors

BMPFileHeader::BMPFileHeader(BMPInfoHeader* infoHeader)
	: fileSize(), fileHeaderSize(13)
{
	//make getters and setters fr the bmpinfoheader to get access to its attributes here

	fileHeaderSize

		//fileHeaderSize + infoHeaderSize + (bytesPerPixel * width + paddingSize) * height

		CreateFileHeader();
}

#pragma endregion

#pragma region Properties

short int BMPFileHeader::GetSize() { return fileHeader.size(); }

#pragma endregion

#pragma region Methods

void BMPFileHeader::CreateFileHeader(short int infoHeaderSize)
{
	/*
		fileHeader[0]-[1]	 = file signature (identifies file as a BMP)
		fileHeader[2]-[5]	 = size of file (bytes)
		fileHeader[6]-[9]	 = reserved
		fileHeader[10]-[13]  = starting position of pixel memory
	*/


	fileHeader[0] = (unsigned char)('B');								// Signature part 1
	fileHeader[1] = (unsigned char)('M');								// Signature part 2
	fileHeader[2] = (unsigned char)(fileSize);							// FileSize part 1
	fileHeader[3] = (unsigned char)(fileSize >> 8);						// FileSize part 2
	fileHeader[4] = (unsigned char)(fileSize >> 16);					// FileSize part 3
	fileHeader[5] = (unsigned char)(fileSize >> 24);					// FileSize part 4
	fileHeader[10] = (unsigned char)(fileHeaderSize + infoHeaderSize);	// Size of the header and info
}

#pragma endregion
