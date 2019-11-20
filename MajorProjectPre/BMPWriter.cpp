#include "BMPWriter.h"


#pragma region Constructors

BMPWriter::BMPWriter() 
	: fileObject(), height(500), width(500), colourSpace(3), bmp(nullptr) 
{
	image = {PixelVector2D(height, PixelVector1D(width, Pixel(RGB())))};
}

BMPWriter::BMPWriter(BMP* bmp) 
	: fileObject(), height(bmp->GetHeight()), width(bmp->GetWidth()), colourSpace(bmp->GetColourSpace()), bmp(bmp)
{
	image = {PixelVector2D(height, PixelVector1D(width, Pixel(RGB())))};
}

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

void BMPWriter::CreateNewBMP()
{
	const int height = 500;
	const int width = 500;
	const int colourElement = 3;

	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			image[i][j].SetRGB(255, 100, 100);

			//std::cout << std::endl;

			//std::cout << "R - ";


			//std::cout << std::endl;

			//std::cout << "G - ";

			//std::cout << std::endl;

			//std::cout << "B - ";

		}
	}

	GenerateImageData(image);

	std::cout << "Image generated" << std::endl;
}

void BMPWriter::GenerateImageData(PixelVector2D image)
{
	// Create an array to store the extra padding
	unsigned char padding[3] = {0, 0, 0};

	// Calculate the amount of padding needed for this image
	int paddingSize = (4 - (width * colourSpace) % 4) % 4;

	// Create a file header
	unsigned char* fileHeader = CreateFileHeader(paddingSize);

	// Create an info header
	unsigned char* infoHeader = CreateInfoHeader();

	// Write the file header
	fwrite(fileHeader, 1, 14, fileObject);

	// Write the info header
	fwrite(infoHeader, 1, 40, fileObject);

	// For each row in the image
	for(int i = 0; i < height; i++)
	{
		// Write the pixel data for each pixel in the width
		fwrite(image. + (i * width * colourSpace), colourSpace, width, fileObject);

		// Add any needed padding to the image
		fwrite(padding, 1, paddingSize, fileObject);
	}

	// Close the file
	fclose(imageFile);
}

unsigned char* BMPWriter::CreateFileHeader(int paddingSize)
{
	// Calculate and store the size of the entire file
	int fileSize = 14 + 40 + (colourSpace * width + paddingSize) * height;

	// Array placed in file that contains key file information
	unsigned char fileHeader[13];
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
	fileHeader[10] = (unsigned char)(14 + 40);							// Size of the header and info

	return fileHeader;
}

unsigned char* BMPWriter::CreateInfoHeader()
{
	unsigned char infoHeader[40];
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

	infoHeader[0] = (unsigned char)(40);					// hs		Set the header size
	infoHeader[4] = (unsigned char)(width);					// w
	infoHeader[5] = (unsigned char)(width >> 8);			// w
	infoHeader[6] = (unsigned char)(width >> 16);			// w		Set the width of the image
	infoHeader[7] = (unsigned char)(width >> 24);			// w
	infoHeader[8] = (unsigned char)(height);				// h
	infoHeader[9] = (unsigned char)(height >> 8);			// h
	infoHeader[10] = (unsigned char)(height >> 16);			// h		Set the height of the image
	infoHeader[11] = (unsigned char)(height >> 24);			// h
	infoHeader[12] = (unsigned char)(1);					// cp		Set the colour plane
	infoHeader[14] = (unsigned char)(colourSpace * 8);		// bpp		Set the number of bits per pixel

	return infoHeader;
}

#pragma endregion