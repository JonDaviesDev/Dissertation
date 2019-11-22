#include "BMPFileHeader.h"

#pragma region Constructors

BMPFileHeader::BMPFileHeader(BMPInfoHeader* infoHeader)
	: fileSize(), fileHeaderSize(fileHeader.max_size())
{
	CreateFileHeader(infoHeader);
}

#pragma endregion

#pragma region Properties

#pragma region Setters

void BMPFileHeader::SetFileHeader(BMPInfoHeader* info)
{
	// Calculate the size of the entire file
	SetFileSize(fileHeaderSize + info->GetSize() + (info->GetBytesPerPixel() * info->GetWidth() + info->GetPaddingSize()) * info->GetHeight());

	SetFileName(info->GetReader()->GetFileName());
}

void BMPFileHeader::SetFileName(const char* value) { fileName = value; }

void BMPFileHeader::SetFileSize(size_t value) { fileSize = value; }

#pragma endregion

#pragma region Getters

const char* BMPFileHeader::GetFileName() { return fileName; }

int BMPFileHeader::GetSize() { return fileHeader.size(); }

size_t BMPFileHeader::GetFileSize() { return fileSize; }

std::array<unsigned char, 14> BMPFileHeader::GetFileData() { return fileHeader; }

FileReader* BMPFileHeader::GetReader() { return reader; }

#pragma endregion

#pragma endregion

#pragma region Methods

void BMPFileHeader::CreateFileHeader(BMPInfoHeader* info)
{
	/*
		fileHeader[0]-[1]	 = file signature (identifies file as a BMP)
		fileHeader[2]-[5]	 = size of file (bytes)
		fileHeader[6]-[9]	 = reserved
		fileHeader[10]-[13]  = starting position of pixel memory
	*/

	SetFileHeader(info);

	fileHeader[0] = (unsigned char)('B');								// Signature part 1
	fileHeader[1] = (unsigned char)('M');								// Signature part 2
	fileHeader[2] = (unsigned char)(fileSize);							// FileSize part 1
	fileHeader[3] = (unsigned char)(fileSize >> 8);						// FileSize part 2
	fileHeader[4] = (unsigned char)(fileSize >> 16);					// FileSize part 3
	fileHeader[5] = (unsigned char)(fileSize >> 24);					// FileSize part 4
	fileHeader[10] = (unsigned char)(fileHeaderSize + info->GetSize());	// Size of the header and info
}

#pragma endregion
