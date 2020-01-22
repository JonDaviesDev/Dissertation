#include "Stego.h"


#pragma region Constructors

Stego::Stego(){}

Stego::Stego(FileReader* coverBMP, FileReader* textFile, const char* newFileName)
	: bmp(coverBMP), text(textFile)
{
	stegoFileName = newFileName;

	bmp.PrintPixels();

	auto a = FindModulus(RoundToInt(FindLength(Pixel(RGB(128, 65, 210)))), 42);
	auto b = FindModulus(RoundToInt(FindLength(Pixel(RGB(12, 150, 150)))), 42);
	auto c = FindModulus(RoundToInt(FindLength(Pixel(RGB(245, 99, 100)))), 42);

	CreatePixelListCopy();

	CreateBinaryList(text);

	BitNumber();

	LSB();

	ModifyBMP(&bmp, newFileName);
}

#pragma endregion

#pragma region Properties

#pragma region Setters



#pragma endregion

#pragma region Getters

int Stego::GetBinaryListSize()
{
	int size = 0;

	for(int i = 0; i < binaryList.size(); i++)
	{
		size += 8;
	}

	return size;
}

const char* Stego::GetStegoFileName() { return stegoFileName; }

#pragma endregion

#pragma endregion

#pragma region Methods

// Convert a single char to its binary representation
std::bitset<8> Stego::CharToBinary(char value)
{
	return std::bitset<8>(value);
}

// Convert a string of text to binary and store in list
void Stego::CreateBinaryList(TextBuffer buffer)
{
	// for every element inside the text buffer
	for(int i = 0; i < buffer.GetBuffer().size(); i++)
	{
		// Covert it to binary and add to list
		binaryList.push_back(CharToBinary(buffer.GetBuffer()[i]));
	}
}

void Stego::BitNumber()
{
	bmp.GetFileHeader()->SetFileHeaderElement((unsigned char)binaryList.size() * 8, 6);
}

void Stego::CreatePixelListCopy()
{
	// Set up a 2D vector and initialise it to pixelList
	pixelList = std::vector<std::vector<RGB>>(bmp.GetHeight(), std::vector<RGB>(bmp.GetWidth()));

	//for each row
	for(int i = 0; i < bmp.GetHeight(); i++)
	{
		// for each element in a column
		for(int j = 0; j < bmp.GetWidth(); j++)
		{
			pixelList[i][j].SetRed(*bmp.GetPixelContainer()->GetRed(j));

			pixelList[i][j].SetGreen(*bmp.GetPixelContainer()->GetGreen(j));

			pixelList[i][j].SetBlue(*bmp.GetPixelContainer()->GetBlue(j));
		}
	}
}

void Stego::LSB()
{
	int k = 0;

	// For each character
	for(int i = 0; i < binaryList.size(); i++)
	{
		//Step through that characters binary representation, bit by bit
		for(int j = 0; j < binaryList[i].size(); j++)
		{
			// If the value ends in an odd number, the LSB has got to be 1.

			// If the value ends in an even number, the LSB has got be 0.

			// Check this against the binary value that we want to embed.  
			// If the pixel value ends in an odd number AND the binary entry is 0, enter condition
			if((pixelList[0][k].GetRed() % 2) == 1 && (binaryList[i][j] % 2) != 1)
			{
				unsigned char temp = pixelList[i][j].GetRed();
			
				//bitwise XOR - swap the value if both are equal (LSB switches from 1 to 0)
				pixelList[0][k].SetRed(temp ^= 1);

			}
			
			k++;
		}
	}
}

void Stego::DistanceToOrigin()
{
	// 
}

void Stego::ModifyBMP(BMP* bmp, const char* newFileName)
{
	PixelContainer pixelContainer(bmp->GetWidth(), bmp->GetHeight());

	int k = 0;

	for(int i = 0; i < bmp->GetHeight(); i++)
	{
		for(int j = 0; j < bmp->GetWidth(); j++)
		{
			pixelContainer.SetRed(pixelList[i][j].GetRed(), k);

			pixelContainer.SetGreen(pixelList[i][j].GetGreen(), k);

			pixelContainer.SetBlue(pixelList[i][j].GetBlue(), k);

			k++;
		}
		
	}

	GenerateImageData(bmp, pixelContainer, newFileName);

	std::cout << "Image generated" << std::endl;

	fclose(bmp->GetFileObject()->GetFile());
}

float Stego::FindLength(Pixel pixel)
{
	return sqrt((pixel.GetRGB().GetRed() * pixel.GetRGB().GetRed()) + (pixel.GetRGB().GetGreen() * pixel.GetRGB().GetGreen()) + (pixel.GetRGB().GetBlue() * pixel.GetRGB().GetBlue()));
}

int Stego::RoundToInt(float value)
{
	return (int)roundf(value);
}

int Stego::FindModulus(int distance, int modValue)
{
	return distance % modValue;
}

void Stego::CheckForFringeValues(int value, int modValue)
{
	if(value != 10 || value != 11)
	{
		// Change pixel colour to match the output of 10 or 11
	}
}

#pragma endregion