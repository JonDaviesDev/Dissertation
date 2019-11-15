#include "BMP.h"


#pragma region Constructors

Pixel::Pixel()
{
	r = 0;
	g = 0;
	b = 0;
}

Pixel::Pixel(unsigned char* data)
{
	r = *data;
	g = *data + 1;
	b = *data + 2;
}

Pixel::Pixel(unsigned char* data, int iterator)
{
	r = data[iterator];
	g = data[iterator + 1];
	b = data[iterator + 2];
}

BMP::BMP()
	: width(0), height(0), size(0), rowPadding(0), fileLocation(nullptr), file(nullptr), pixels()
{}

#pragma endregion

#pragma region Properties

void BMP::SetHeaderInfomation(char* bmpHeaderInfo, const char* filePath, FILE* file)
{
	fread(bmpHeaderInfo, sizeof(char), 54, file);

	fileLocation = filePath;

	width = *(int*)&bmpHeaderInfo[18];
	height = *(int*)&bmpHeaderInfo[22];

	size = width * height * 3;
}

void BMP::SetPixelData(unsigned char* data, int iterator)
{
	pixels.push_back(Pixel(data, iterator));
}

void BMP::SetPixelData(BMP* bmp, unsigned char* data, int iterator)
{
	bmp->pixels.push_back(Pixel(data, iterator));
}

#pragma endregion

#pragma region Methods

BMP* BMP::ScanBMP(const char* filePath, const char* openMode)
{
	FILE* file = nullptr;

	char bmpHeaderInfo[54] = {0};

	if((file = ErrorCheck(file, filePath, openMode)) != 0)
	{
		SetHeaderInfomation(bmpHeaderInfo, filePath, file);

		DisplayHeaderInformation();

		ReadPixels(file);

		fclose(file);

		return this;
	}
	else
	{
		return nullptr;
	}

}

FILE* BMP::LoadBMP(BMP& bmp, const char* openMode)
{
	FILE* file = nullptr;

	file = ErrorCheck(file, bmp.fileLocation, openMode);

	if(file != nullptr)
	{
		fclose(file);

		return file;
	}
	else
	{
		fclose(file);

		return nullptr;
	}
}

unsigned int BMP::CalculatePadding()
{
	return (unsigned int)(this->width * 3 + 3) & (~3);
}

void BMP::ReadPixels(FILE* file)
{
	int pixelCount = 0;
	int rowCount = 0;
	int columnCount = 0;
	int rgbElements = 0;
	int pixels = 0;

	unsigned int rowPadding = CalculatePadding();

	unsigned char* data = new unsigned char[rowPadding];

	for(int i = 0; i < this->height; i++)
	{
		fread(data, sizeof(unsigned char), rowPadding, file);

		for(int j = 0; j < this->width * 3; j += 3)
		{
			ConvertBGRtoRGB(data, j);

			SetPixelData(data, j);

			//DisplayRGBValues(data, j);

			rgbElements += 3;
			pixels++;
		}
		columnCount++;
		rowCount++;
	}

	pixelCount = rowCount * columnCount;

	std::cout << std::endl << "Rows: " << rowCount << " Columns: " << columnCount << " Pixels: " << pixels << std::endl;
	std::cout << "RGB Elements: " << rgbElements << std::endl;

	fclose(file);
}

void BMP::Write(const char* fileName)
{
	const int height = 500;
	const int width = 500;
	const int colourElement = 3;

	unsigned char image[width][height][3];

	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			image[i][j][2] = (unsigned char)254; //red

			std::cout << std::endl;

			std::cout << "R - ";

			DisplayBinaryTest(image[i][j][2]);

			image[i][j][1] = (unsigned char)100; //green

			std::cout << std::endl;

			std::cout << "G - ";

			DisplayBinaryTest(image[i][j][1]);

			std::cout << std::endl;

			std::cout << "B - ";

			image[i][j][0] = (unsigned char)100; //blue

			DisplayBinaryTest(image[i][j][0]);
		}
	}

	generateBitmapImage((unsigned char*)image, height, width, fileName);

	std::cout << "Image generated" << std::endl;
}

void BMP::Write(BMP bmp)
{
	const int height = bmp.height;
	const int width = bmp.width;
	
	std::vector<std::vector<std::vector<unsigned char>>> image((unsigned char)bmp.height, std::vector<std::vector<unsigned char>>(bmp.width, std::vector<unsigned char>(3)));

	for(int i = 0; i < bmp.height; i++)
	{
		for(int j = 0; j < bmp.width; j++)
		{
			image[i][j][2] = bmp.pixels[i].r; //red

			image[i][j][2] |= 1;

			image[i][j][1] = bmp.pixels[i].g; //green

			image[i][j][1] |= 1;

			image[i][j][0] = bmp.pixels[i].b; //blue

			image[i][j][0] |= 1;
		}
	}

	GenerateBitmapImage(image, *this);
}

FILE* BMP::ErrorCheck(FILE* file, const char* filePath, const char* openMode)
{
	errno_t error = NULL;
	char errorMessageBuffer[95];	// Maximum error message length is 94 chars. +1 for null terminator

	if((error = fopen_s(&file, filePath, openMode)) != 0)
	{
		strerror_s(errorMessageBuffer, sizeof(errorMessageBuffer), error);

		std::cout << "Cannot open file '" << filePath << "' : " << errorMessageBuffer << std::endl;

		return NULL;
	}

	else
	{
		strerror_s(errorMessageBuffer, sizeof(errorMessageBuffer), error);

		std::cout << "'" << filePath << "' " << "opened successfully in '" << openMode << "' mode" << std::endl;
		std::cout << errorMessageBuffer << std::endl;

		return file;
	}
}

void BMP::generateBitmapImage(unsigned char* image, int height, int width, const char* imageFileName)
{
	// Create an array to store the extra padding
	unsigned char padding[3] = {0, 0, 0};

	// Calculate the amount of padding needed for this image
	int paddingSize = (4 - (width * bytesPerPixel) % 4) % 4;

	// Create a file header
	unsigned char* fileHeader = createBitmapFileHeader(height, width, paddingSize);

	// Create an info header
	unsigned char* infoHeader = createBitmapInfoHeader(height, width);

	// Ensure that the file can be opened, ErrorCheck will return nullptr if file cannot be opened
	FILE* imageFile = ErrorCheck(file, imageFileName, "wb");

	// Write the file header
	fwrite(fileHeader, 1, fileHeaderSize, imageFile);

	// Write the info header
	fwrite(infoHeader, 1, infoHeaderSize, imageFile);

	// For each row in the image
	for(int i = 0; i < height; i++)
	{
		// Write the pixel data for each pixel in the width
		fwrite(image + (i * width * bytesPerPixel), bytesPerPixel, width, imageFile);

		// Add any needed padding to the image
		fwrite(padding, 1, paddingSize, imageFile);
	}

	// Close the file
	fclose(imageFile);
}

void BMP::GenerateBitmapImage(std::vector<std::vector<std::vector<unsigned char>>> image, BMP bmp)
{
	// Create an array to store the extra padding
	unsigned char padding[3] = {0, 0, 0};

	// Calculate the amount of padding needed for this image
	int paddingSize = (4 - (bmp.width * bmp.bytesPerPixel) % 4) % 4;

	// Create a file header
	unsigned char* fileHeader = createBitmapFileHeader(bmp.height, bmp.width, paddingSize);

	// Create an info header
	unsigned char* infoHeader = createBitmapInfoHeader(bmp.height, bmp.width);

	// Ensure that the file can be opened, ErrorCheck will return nullptr if file cannot be opened
	FILE* imageFile = ErrorCheck(file, bmp.fileLocation, "wb");

	// Write the file header
	fwrite(fileHeader, 1, bmp.fileHeaderSize, imageFile);

	// Write the info header
	fwrite(infoHeader, 1, bmp.infoHeaderSize, imageFile);

	int j = 0;

	// For each row in the image
	for(int i = 0; i < bmp.height; i++)
	{
		for(int j = 0; j < bmp.width; j++)
		{
			// Write the pixel data for each pixel in the width
			fwrite(&image[i][j] + (j * width * bytesPerPixel), bytesPerPixel, width, imageFile);
		}
		// Add any needed padding to the image
		fwrite(padding, 1, paddingSize, imageFile);
	}

	// Close the file
	fclose(imageFile);
}

unsigned char* BMP::createBitmapFileHeader(int height, int width, int paddingSize)
{
	// Calculate and store the size of the entire file
	int fileSize = fileHeaderSize + infoHeaderSize + (bytesPerPixel * width + paddingSize) * height;

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
	fileHeader[10] = (unsigned char)(fileHeaderSize + infoHeaderSize);	// Size of the header and info

	return fileHeader;
}

unsigned char* BMP::createBitmapInfoHeader(int height, int width)
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

	infoHeader[0] = (unsigned char)(infoHeaderSize);		// hs		Set the header size
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

	return infoHeader;
}

void BMP::ConvertBGRtoRGB(unsigned char* data, int iteration)
{
	unsigned char temp = 0;

	temp = data[iteration];
	data[iteration] = data[iteration + 2];
	data[iteration + 2] = temp;
}

std::bitset<8> BMP::GetBinary8(unsigned char p)
{
	return std::bitset<8>(p);
}

std::string BMP::ReadTextFile()
{
	std::ifstream in("sampleText.txt", std::ios::binary);

	std::vector<std::bitset<8>> bin;

	if(in)
	{		
		std::string str;

		while(std::cin >> str)
		{
			bin.push_back(std::bitset<8>(str));
		}
	}
	else
	{
		return NULL;
	}
}

#pragma region DisplayFunctions

void BMP::DisplayHeaderInformation()
{
	std::cout << std::endl << "Image width: " << this->width << std::endl;
	std::cout << "Image height: " << this->height << std::endl;
	std::cout << "Image size: " << this->size << " bytes" << std::endl << std::endl;
}

void BMP::DisplayRGBValues(unsigned char* data, int& iteration)
{
	std::cout << "R: " << (int)data[iteration] << " G: " << (int)data[iteration + 1] << " B: " << (int)data[iteration + 2] << std::endl;
}

void BMP::DisplayHexValues(unsigned char* data, int& iteration, int& pixels)
{
	std::cout << std::dec << "Pixel " << pixels << " : ";
	std::cout << std::hex << (int)data[iteration] << " " << (int)data[iteration + 1] << " " << (int)data[iteration + 2] << std::dec << std::endl;
}

void BMP::DisplayBinaryTest(unsigned char p)
{
	std::cout << std::endl << "Before: " << GetBinary8(p) << std::endl;

	p |= 1;

	std::cout << "After: " << GetBinary8(p) << std::endl;
}

#pragma endregion

#pragma endregion



/*void BMP::WriteToBMP(BMP& bmp)
{
	int pixelCount = 0;
	int rowCount = 0;
	int columnCount = 0;
	int rgbElements = 0;
	int pixels = 0;

	FILE* file = ErrorCheck(bmp.file, bmp.fileLocation, "wb");

	//char buffer[3] = {100, 100, 100};

	//unsigned int rowPadding = CalculatePadding();

	//unsigned char* data = new unsigned char[rowPadding];

	int padSize = (4 - (bmp.width * 3) % 4) % 4;
	int sizeData = bmp.width * bmp.height * 3 + bmp.height * padSize;
	int sizeAll = sizeData + sizeof(file) + (sizeof(char) * 54);
	unsigned char pad[3] = {0,0,0};
	unsigned char pix[3] = {0, 255, 0};

	for(int i = 0; i < bmp.height; i++)
	{
		for(int j = 0; j < bmp.width; j++)
		{
			fseek(file, i, SEEK_SET);

			fwrite(pix, bmp.width, sizeof(unsigned char) * 3, file);

		}

		fwrite(pad, 1, (4 - (bmp.width * 3) % 4) % 4, file);
	}

	/*for(int i = 28; i < bmp.height; i++)
	{
		for(int j = 0; j < bmp.width * 3; j += 3)
		{
			fwrite(&buffer, 3, 3, bmp.file);
		}
	}
}*/
