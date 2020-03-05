#include "Stego.h"



#pragma region Constructors

Stego::Stego(){}

Stego::Stego(FileLoader* coverBMP, FileLoader* textFile, const char* newFileName)
	: bmp(coverBMP), text(textFile), stegoFileName(newFileName)
{
	//bmp.PrintPixels();

	auto a = FindModulus(RoundToInt(FindLength(Pixel(cRGB(128, 65, 210)))), 42);
	auto b = FindModulus(RoundToInt(FindLength(Pixel(cRGB(12, 150, 150)))), 42);
	auto c = FindModulus(RoundToInt(FindLength(Pixel(cRGB(245, 99, 100)))), 42);

	CreatePixelListCopy();

	CreateBinaryList(text);

	InitialiseRemainderTable(0);

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
	pixelList = std::vector<std::vector<cRGB>>(bmp.GetHeight(), std::vector<cRGB>(bmp.GetWidth()));

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
				unsigned char tempRED = pixelList[i][j].GetRed();
			
				//bitwise XOR - swap the value if both are equal (LSB switches from 1 to 0)
				pixelList[0][k].SetRed(tempRED ^= 1);

			}
			
			k++;
		}
	}
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






// returning an int for testing purposes


// To get the remainder from 2 to 10, we increase the value of each component by 5.




// - testing to see how best to change the remainder value
int Stego::DistanceToOrigin(Pixel pixel, int modulusValue)
{
	/*for(int i = 0; i < pixelList.size(); i++)
	{
		for(int j = 0; j < pixelList[i].size(); j++)
		{
			int result = FindModulus(RoundToInt(FindLength(pixelList[i][j])), 42);
		}
	}*/

	int length = RoundToInt(FindLength(pixel));

	int remainder = FindModulus(length, modulusValue);

	if(remainder < 10)
	{
		// find out how far from 10 it is

		int temp = abs(remainder - 10);


	}
	if(remainder > 10 && remainder <= 21)
	{
		// find out how far from 11 it is
	}
	if(remainder < 30)
	{
		// find out how far from 30 it is
	}
	if(remainder > 31)
	{
		// find out how far from 31 it is
	}

	return FindModulus(RoundToInt(FindLength(pixel)), 42);
}

void Stego::InitialiseRemainderTable(int startingValue)
{
	int temp = startingValue;

	//remainderTable.Add(temp++,  6, 3); // remainder 1
	//remainderTable.Add(temp++,  5, 3); // remainder 2
	//remainderTable.Add(temp++,  , 1); // remainder 3
	//remainderTable.Add(temp++,  1, 3); // remainder 4
	//remainderTable.Add(temp++,  ); // remainder 5
	//remainderTable.Add(temp++,  ); // remainder 6
	//remainderTable.Add(temp++,  ); // remainder 7
	//remainderTable.Add(temp++,  ); // remainder 8
	//remainderTable.Add(temp++,  ); // remainder 9
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

int Stego::DetermineSegment(int value, int modValue)
{
	// Basic error checking - Make sure that the value does not fall out of the allowed range
	if(value < 0 || value > modValue)
	{
		if(value < 0)
		{
			std::cout << "STEGO::DETERMINESEGEMENT::VALUE_CANNOT_BE_LESS_THAN_ZERO" << std::endl;
		}
		
		if(value > modValue)
		{
			std::cout << "STEGO::DETERMINESEGEMENT::VALUE_CANNOT_BE_GREATER_THAN_MODULUS_VALUE" << std::endl;
		}

		exit(-1);
	}

	if(value >= 0 && value <= (modValue / 2))
	{
		return 0;
	}
	else return 1;

}

void Stego::CheckEdgesOfScale(int segment, int value, int modValue)
{
	if(segment)
	{
		// If the value does not equal the centre of the right segment (+/- 1 either side), then enter
		if(value != (modValue + (modValue * 0.25)) || value != (modValue + (modValue * 0.25) + 1) || value != (modValue + (modValue * 0.25) - 1))
		{
			// Change the RGB values of the pixel to make the value sit in the centre of the right segment and re-calcualate
		}
	}
	else
	{
		// If the value does not equal the centre of the left segment (+/- 1 either side), then enter
		if(value != (modValue + (modValue / 2)) || value != (modValue + (modValue / 2) + 1) || value != (modValue + (modValue / 2) - 1))
		{
			// Change the RGB values of the pixel to make the value sit in the centre of the lef segment and re-calcualate
		}
	}
}

#pragma endregion