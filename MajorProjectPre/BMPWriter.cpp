#include "BMPWriter.h"


#pragma region Constructors

BMPWriter::BMPWriter() 
	: fileName(nullptr), fileObject(nullptr), height(0), width(0), colourSpace(0), bmp(nullptr) {}

BMPWriter::BMPWriter(BMP* bmp) 
	: fileName(nullptr), fileObject(nullptr), height(bmp->GetHeight()), 
	width(bmp->GetWidth()), colourSpace(bmp->GetColourSpace()), bmp(bmp) {}

#pragma endregion

#pragma region Properties

#pragma region Setters

void BMPWriter::SetHeight(int value) { height = value; }

void BMPWriter::SetWidth(int value) { width = value; }

void BMPWriter::SetColourSpace(int value) { colourSpace = value; }

#pragma endregion

#pragma region Getters

int BMPWriter::GetHeight() { return height; }

int BMPWriter::GetWidth() { return width; }

int BMPWriter::GetColourSpace() { return colourSpace; }

#pragma endregion

#pragma endregion

#pragma region Methods

void BMPWriter::CreateNewBMP(const char* fileName, int width, int height, RGB colour)
{
	PixelContainer pixelContainer(width, height);

	for(int i = 0; i < height * width; i++)
	{
		pixelContainer.SetRed((unsigned char)colour.GetRed(), i);
		pixelContainer.SetGreen((unsigned char)colour.GetGreen(), i);
		pixelContainer.SetBlue((unsigned char)colour.GetBlue(), i);
	}

	GenerateImageData(pixelContainer, height, width, fileName);

	std::cout << "Image generated" << std::endl;
}

void BMPWriter::CreateNewBMP(BMP* bmp)
{
	PixelContainer pixelContainer(bmp->GetWidth(), bmp->GetHeight());

	for(int i = 0; i < bmp->GetHeight() * bmp->GetWidth(); i++)
	{
		pixelContainer.SetRed((unsigned char)bmp->GetPixelContainer()->GetRed(i), i);
		pixelContainer.SetGreen((unsigned char)bmp->GetPixelContainer()->GetGreen(i), i);
		pixelContainer.SetBlue((unsigned char)bmp->GetPixelContainer()->GetBlue(i), i);
	}

	GenerateImageData(bmp, pixelContainer);

	std::cout << "Image generated" << std::endl;
}

void BMPWriter::WriteBMP(BMP* bmp)
{
	CreateNewBMP(bmp);
}

void BMPWriter::GenerateImageData(BMP* bmp, PixelContainer pixelContainer)
{
	// Create an array to store the extra padding
	unsigned char padding[3] = {0, 0, 0};

	// Calculate the amount of padding needed for this image
	int paddingSize = (4 - (bmp->GetWidth() * 3) % 4) % 4;

	// Create a file header
	unsigned char* fileHeader = CreateFileHeader(bmp->GetHeight(), bmp->GetWidth(), bmp->GetInfoHeader()->GetPaddingSize());

	// Create an info header
	unsigned char* infoHeader = CreateInfoHeader(bmp->GetHeight(), bmp->GetWidth());

	// Ensure that the file can be opened, ErrorCheck will return nullptr if file cannot be opened
	FILE* imageFile = ErrorCheck(bmp->GetFileObject()->GetFile(), bmp->GetFileHeader()->GetFileName(), "wb");

	// Write the file header
	fwrite(fileHeader, 1, 14, imageFile);

	// Write the info header
	fwrite(infoHeader, 1, 40, imageFile);

	// For each row in the image
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			fwrite(pixelContainer.GetBlue(j), sizeof(char), 1, imageFile);
			fwrite(pixelContainer.GetGreen(j), sizeof(char), 1, imageFile);
			fwrite(pixelContainer.GetRed(j), sizeof(char), 1, imageFile);
		}

		fwrite(padding, 1, paddingSize, imageFile);
	}

	// Close the file
	fclose(imageFile);
}

void BMPWriter::GenerateImageData(PixelContainer PixelContainer, int height, int width, const char* imageFileName)
{
	// Create an array to store the extra padding
	unsigned char padding[3] = {0, 0, 0};

	// Calculate the amount of padding needed for this image
	int paddingSize = (4 - (width * 3) % 4) % 4;

	// Create a file header
	unsigned char* fileHeader = CreateFileHeader(height, width, paddingSize);

	// Create an info header
	unsigned char* infoHeader = CreateInfoHeader(height, width);

	// Ensure that the file can be opened, ErrorCheck will return nullptr if file cannot be opened
	FILE* imageFile = ErrorCheck(fileObject, imageFileName, "wb");

	// Write the file header
	fwrite(fileHeader, 1, 14, imageFile);

	// Write the info header
	fwrite(infoHeader, 1, 40, imageFile);

	// For each row in the image
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			fwrite(PixelContainer.GetBlue(j), sizeof(char), 1, imageFile);
			fwrite(PixelContainer.GetGreen(j), sizeof(char), 1, imageFile);
			fwrite(PixelContainer.GetRed(j), sizeof(char), 1, imageFile);
		}

		fwrite(padding, 1, paddingSize, imageFile);		
	}

	// Close the file
	fclose(imageFile);
}

unsigned char* BMPWriter::CreateFileHeader(int height, int width, int paddingSize)
{
	// Calculate and store the size of the entire file
	int fileSize = 14 + 40 + (3 * width + paddingSize) * height;
		
	// Array placed in file that contains key file information
	static unsigned char fileHeader[13];
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
	fileHeader[10] = (unsigned char)(14 + 40);	// Size of the header and info

	return fileHeader;
}

unsigned char* BMPWriter::CreateInfoHeader(int height, int width)
{
	static unsigned char infoHeader[40];
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

	infoHeader[0] = (unsigned char)(40);		// hs		Set the header size
	infoHeader[4] = (unsigned char)(width);					// w
	infoHeader[5] = (unsigned char)(width >> 8);			// w
	infoHeader[6] = (unsigned char)(width >> 16);			// w		Set the width of the image
	infoHeader[7] = (unsigned char)(width >> 24);			// w
	infoHeader[8] = (unsigned char)(height);				// h
	infoHeader[9] = (unsigned char)(height >> 8);			// h
	infoHeader[10] = (unsigned char)(height >> 16);			// h		Set the height of the image
	infoHeader[11] = (unsigned char)(height >> 24);			// h
	infoHeader[12] = (unsigned char)(1);					// cp		Set the colour plane
	infoHeader[14] = (unsigned char)(3 * 8);	// bpp		Set the number of bits per pixel

	return infoHeader;
}

FILE* BMPWriter::ErrorCheck(FILE* file, const char* filePath, const char* mode)
{
	errno_t error = NULL;
	char errorMessageBuffer[95];	// Maximum error message length is 94 chars. +1 for null terminator

	if((error = fopen_s(&file, filePath, mode)) != 0)
	{
		strerror_s(errorMessageBuffer, sizeof(errorMessageBuffer), error);

		std::cout << "Cannot open file '" << filePath << "' : " << errorMessageBuffer << std::endl;

		return NULL;
	}

	else
	{
		strerror_s(errorMessageBuffer, sizeof(errorMessageBuffer), error);

		std::cout << "'" << filePath << "' " << "opened successfully in '" << mode << "' mode" << std::endl;
		std::cout << errorMessageBuffer << std::endl;

		return file;
	}
}

#pragma endregion
